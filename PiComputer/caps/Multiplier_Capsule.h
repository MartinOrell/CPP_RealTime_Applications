#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Multiplier_Capsule: public mrt::Capsule{
    public:
        Multiplier_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(const mrt::Message& message);
        
        void connectAdder(int adderId);
        
    private:
        void sendReturnIncrementMessage(int toId, double inc);

        void handleMessage(const mrt::GetIncrement& message);

        int _id;
        int _adderId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
};