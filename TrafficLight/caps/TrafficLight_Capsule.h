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
        int getId();
        void start();
        void handleMessage(const mrt::Message& message);
        
    private:
        void handleTimeout(const mrt::TimeoutMessage& message);

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{Red, Green, Yellow};
        State _state;
};