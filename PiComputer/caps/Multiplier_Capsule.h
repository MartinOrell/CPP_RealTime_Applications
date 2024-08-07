#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include <cmath>

class CapsuleRunner;

class Multiplier_Capsule: public Capsule{
    public:
        Multiplier_Capsule(int id, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connectAdder(int adderId);
        
    private:
        void sendReturnIncrementMessage(int toId, double inc);

        void handleMessage(GetIncrement message);

        int _id;
        int _adderId;
        CapsuleRunner* _capsuleRunnerPtr;
};