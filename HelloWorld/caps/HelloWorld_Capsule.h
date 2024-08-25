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
        int getId() override;
        void start() override;
        void handleMessage(const mrt::Message&) override;
        
    private:
        void handleTimeout(const mrt::TimeoutMessage&);

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{
            S1,S2
        };
        State _state;
};