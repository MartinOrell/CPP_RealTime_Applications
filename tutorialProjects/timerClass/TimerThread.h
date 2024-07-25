#pragma once

#include "MessageHandler.h"
#include <chrono>
#include <thread>
#include <vector>
#include <stop_token>
#include <algorithm>

class TimerThread{
    public:
        TimerThread(MessageHandler<int>*);
        void run();
        void stop();
        int informIn(std::chrono::steady_clock::duration);
        int informEvery(std::chrono::steady_clock::duration);
        void cancelTimer(int);
    private:

        struct Timer{
            int id;
            std::chrono::steady_clock::time_point timeoutTime;
            bool isRepeating;
            std::chrono::steady_clock::duration interval;

            bool operator<(Timer a){
                return timeoutTime < a.timeoutTime;
            }
        };

        MessageHandler<int>* _outMessageHandlerPtr;
        MessageHandler<Timer> _inMessageHandler;
        MessageHandler<int> _inCancelTimerHandler;
        std::jthread _thread;
        std::vector<Timer> _timers;
        int _nextId;
};