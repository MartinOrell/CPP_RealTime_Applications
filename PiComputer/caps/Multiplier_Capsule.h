#pragma once

#include "Capsule.h"

#include "Message.h"
#include "MessageHandler.h"
#include <cmath>

class Multiplier_Capsule: public Capsule{
    public:
        Multiplier_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connectAdder(int adderId);
        
    private:
        void sendReturnIncrementMessage(int toId, double inc);

        void handleMessage(GetIncrement message);

        int _id;
        int _adderId;
        MessageHandler<SendMessage>* _messageHandlerPtr;
};