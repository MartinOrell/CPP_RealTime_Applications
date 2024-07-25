#include "TimerThread.h"

TimerThread::TimerThread(MessageHandler<int>* messageHandlerPtr){
    _outMessageHandlerPtr = messageHandlerPtr;
    _nextId = 0;
}

void TimerThread::run(){
    _thread = std::jthread([this](std::stop_token stop_token){
        while(!stop_token.stop_requested()){
            
            if(_timers.size() == 0){
                _inMessageHandler.waitForMessage();
                if(stop_token.stop_requested()){
                    break;
                }
                Timer message = _inMessageHandler.popMessage();
                _timers.push_back(message);
            }
            else{
                auto nextTimerToTimeout = std::min_element(_timers.begin(), _timers.end());
                if(_inMessageHandler.waitForMessageUntil(nextTimerToTimeout->timeoutTime)){
                    if(stop_token.stop_requested()){
                        break;
                    }
                    Timer message = _inMessageHandler.popMessage();
                    _timers.push_back(message);
                }

                if(_inCancelTimerHandler.hasMessage()){
                    int m_id = _inCancelTimerHandler.popMessage();
                    _timers.erase(std::remove_if(_timers.begin(), _timers.end(),[m_id](Timer t) { return (t.id == m_id); }), _timers.end());
                }
            }
            auto now = std::chrono::steady_clock::now();
            for(auto it = _timers.begin(); it!=_timers.end();){
                if(now >= it->timeoutTime){
                    _outMessageHandlerPtr->addMessage(it->id);
                    if(it->isRepeating){
                        it->timeoutTime+=it->interval;
                    }
                    else{
                        it = _timers.erase(it);
                    }
                }
                else{
                    it++;
                }
            }
        }
    });
}

void TimerThread::stop(){
    _thread.request_stop();
    _inMessageHandler.stop();
}

int TimerThread::informIn(std::chrono::steady_clock::duration duration){
    Timer timer;
    timer.id = _nextId++;
    timer.timeoutTime = std::chrono::steady_clock::now() + duration;
    timer.isRepeating = false;
    _inMessageHandler.addMessage(timer);
    return timer.id;
}

int TimerThread::informEvery(std::chrono::steady_clock::duration interval){
    Timer timer;
    timer.id = _nextId++;
    timer.timeoutTime = std::chrono::steady_clock::now() + interval;
    timer.isRepeating = true;
    timer.interval = interval;
    _inMessageHandler.addMessage(timer);
    return timer.id;
}

void TimerThread::cancelTimer(int id){
    _inCancelTimerHandler.addMessage(id);
}