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
                    it = _timers.erase(it);
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
    timer.id = _nextId;
    _nextId++;
    timer.timeoutTime = std::chrono::steady_clock::now() + duration;
    _inMessageHandler.addMessage(timer);
    return timer.id;
}

