#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"

class Pong_Capsule{
    public:
        Pong_Capsule(int id, int connectionToId, MessageHandler<Message>*messageHandlerPtr);
        void start();
        void handleMessage(MessageToPong message);
        void handleTimeout(TimeoutMessage message);
    private:
        int _id;
        int _connectionToId;
        MessageHandler<Message>* _messageHandlerPtr;
};