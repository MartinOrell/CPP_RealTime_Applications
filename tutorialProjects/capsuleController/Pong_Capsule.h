#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"

class Pong_Capsule{
    public:
        Pong_Capsule();
        Pong_Capsule(int id, int connectionId, MessageHandler<Message>*messageHandlerPtr, TimerThread* timerThreadPtr);
        void start();
        void handleMessage(MessageToPong message);
        void handleTimeout(TimeoutMessage message);
    private:
        int _id;
        int _connectionId;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
};