#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class TrafficLight_Capsule: public mrt::Capsule{
    public:
        TrafficLight_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId() override;
        void start() override;
        void handleMessage(const mrt::Message&) override;
        
    private:
        void handleTimeout(const mrt::TimeoutMessage&);

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{Red, Green, Yellow};
        State _state;
};