#include "TimerThread.h"

TimerThread::TimerThread(MessageHandler<SendMessage>* messageHandlerPtr){
    _outMessageHandlerPtr = messageHandlerPtr;
    _nextId = 0;
}

void TimerThread::run(){
    _thread = std::jthread([this](std::stop_token stop_token){
        while(!stop_token.stop_requested()){
            
            bool hasReceivedMessage;
            if(_timers.size() == 0){
                _inMessageHandler.waitForMessage();
                hasReceivedMessage = true;
            }
            else{
                auto nextTimerToTimeout = std::min_element(_timers.begin(), _timers.end());
                hasReceivedMessage = _inMessageHandler.waitForMessageUntil(nextTimerToTimeout->timeoutTime);
            }

            if(stop_token.stop_requested()){
                break;
            }

            if(hasReceivedMessage){
                InMessage message = _inMessageHandler.receiveMessage();
                if(std::holds_alternative<Timer>(message)){
                    Timer timer = std::get<Timer>(message);
                    _timers.push_back(timer);
                }
                else{ //cancel Timer message
                    int m_id = std::get<int>(message);
                    _timers.erase(std::remove_if(_timers.begin(), _timers.end(),[m_id](Timer t) { return (t.id == m_id); }), _timers.end());
                }
            }

            //Check for timeouts and send Timeout Messages
            auto now = std::chrono::steady_clock::now();
            for(auto it = _timers.begin(); it!=_timers.end();){

                if(now < it->timeoutTime){
                    it++;
                    continue;
                }

                //Timeout reached
                int timeouts = 1;
                if(it->isRepeating){
                    int timeouts = 1 + (now-it->timeoutTime)/it->interval;
                }
                mergeOrSendTimeoutMessage(it->toId, it->id, timeouts);

                if(it->isRepeating){
                    it->timeoutTime+=it->interval*timeouts;
                    it++;
                }
                else{
                    it = _timers.erase(it);
                }
            }
        }
    });
}

void TimerThread::stop(){
    _thread.request_stop();
    _inMessageHandler.stop();
}

int TimerThread::informIn(int toId, std::chrono::steady_clock::duration duration){
    Timer timer;
    timer.id = _nextId++;
    timer.toId = toId;
    timer.timeoutTime = std::chrono::steady_clock::now() + duration;
    timer.isRepeating = false;
    _inMessageHandler.sendMessage(timer);
    return timer.id;
}

int TimerThread::informEvery(int toId, std::chrono::steady_clock::duration interval){
    assert(interval > std::chrono::nanoseconds(0));
    Timer timer;
    timer.id = _nextId++;
    timer.toId = toId;
    timer.timeoutTime = std::chrono::steady_clock::now() + interval;
    timer.isRepeating = true;
    timer.interval = interval;
    _inMessageHandler.sendMessage(timer);
    return timer.id;
}

void TimerThread::cancelTimer(int id){
    _inMessageHandler.sendMessage(id);
}

void TimerThread::mergeOrSendTimeoutMessage(int toId, int timerId, int timeouts){
    TimeoutMessage message;
    message.timerId = timerId;
    message.timeouts = timeouts;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = message;
    _outMessageHandlerPtr->mergeOrSendMessage(sendMessage);
}