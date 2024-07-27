#pragma once

#include <chrono>
#include <thread>
#include <vector>
#include <stop_token>
#include <algorithm>
#include <variant>
#include "Message.h"
#include "MessageHandler.h"

class TimerThread{
    public:
        TimerThread(MessageHandler<Message>*);
        void run();
        void stop();
        int informIn(int, std::chrono::steady_clock::duration);
        int informEvery(int, std::chrono::steady_clock::duration);
        void cancelTimer(int);
    private:

        struct Timer{
            int id;
            int toId;
            std::chrono::steady_clock::time_point timeoutTime;
            bool isRepeating;
            std::chrono::steady_clock::duration interval;

            bool operator<(Timer a){
                return timeoutTime < a.timeoutTime;
            }
        };

        typedef std::variant<Timer, int> InMessage;

        MessageHandler<Message>* _outMessageHandlerPtr;
        MessageHandler<InMessage> _inMessageHandler;
        std::jthread _thread;
        std::vector<Timer> _timers;
        int _nextId;
};