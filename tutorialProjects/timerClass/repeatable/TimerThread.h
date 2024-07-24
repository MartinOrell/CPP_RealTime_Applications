#pragma once

#include "MessageHandler.h"
#include <chrono>
#include <thread>
#include <vector>
#include <stop_token>

class TimerThread{
    public:
        TimerThread(MessageHandler<int>*);
        void run();
        int informIn(std::chrono::steady_clock::duration);
        int informEvery(std::chrono::steady_clock::duration);
        void cancelTimer(int);
    private:

        struct Timer{
            int id;
            std::chrono::steady_clock::time_point timeoutTime;
            bool isRepeating;
            std::chrono::steady_clock::duration interval;
        };

        MessageHandler<int>* _outMessageHandlerPtr;
        MessageHandler<Timer> _inMessageHandler;
        std::jthread _thread;
        std::vector<Timer> _timers;
        int _nextId;
};