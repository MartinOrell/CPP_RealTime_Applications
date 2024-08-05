#pragma once

#include <chrono>
#include <thread>
#include <vector>
#include <stop_token>
#include <algorithm>
#include <variant>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"

class TimerThread{
    public:
        TimerThread(MessageHandler<SendMessage>*);
        void run();
        void stop();
        int informIn(int, std::chrono::steady_clock::duration);
        int informEvery(int, std::chrono::steady_clock::duration);
        void cancelTimer(int);
    private:
        void mergeOrSendTimeoutMessage(int toId, int timerId, int timeouts);
        MessageHandler<SendMessage>* _outMessageHandlerPtr;
        MessageHandler<SendMessage> _inMessageHandler;
        std::jthread _thread;
        std::vector<Timer> _timers;
        int _nextId;
};