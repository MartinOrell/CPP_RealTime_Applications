#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>

class Ping_Capsule{
    public:
        Ping_Capsule(int id, int connectionToId, MessageHandler<Message>*messageHandlerPtr, TimerThread* timerThreadPtr);
        void start();
        void handleMessage(MessageToPing message);
        void handleTimeout(TimeoutMessage message);
    private:
        int _id;
        int _connectionToId;
        int _count;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
};