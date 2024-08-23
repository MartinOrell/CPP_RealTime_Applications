#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class HelloWorld_Capsule: public mrt::Capsule{
    public:
        HelloWorld_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(const mrt::Message& message);
        
    private:
        void handleTimeout(const mrt::TimeoutMessage& message);

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{
            S1,S2
        };
        State _state;
};