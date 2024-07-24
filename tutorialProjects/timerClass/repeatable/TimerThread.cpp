#include "TimerThread.h"

TimerThread::TimerThread(MessageHandler<int>* messageHandlerPtr){
    _outMessageHandlerPtr = messageHandlerPtr;
    _nextId = 0;
}

void TimerThread::run(){
    _thread = std::jthread([this](std::stop_token stop_token){
        while(!stop_token.stop_requested()){
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

            while(_inMessageHandler.hasMessage()){
                Timer message = _inMessageHandler.popMessage();
                _timers.push_back(message);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
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