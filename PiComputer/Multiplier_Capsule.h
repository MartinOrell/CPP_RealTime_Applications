#pragma once

#include "Message.h"
#include "MessageHandler.h"
#include <cmath>

class Multiplier_Capsule{
    public:
        Multiplier_Capsule(MessageHandler<Message>*messageHandlerPtr);
        void start();
        void handleMessage(GetIncrement message);
    private:
        MessageHandler<Message>* _messageHandlerPtr;
};