#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <chrono>
#include <stdexcept>

namespace mrt{
    class CapsuleRunner;
}

class TrafficLight_Capsule: public mrt::Capsule{
    public:
        TrafficLight_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);
        
    private:
        void handleTimeout(mrt::TimeoutMessage message);

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{Red, Green, Yellow};
        State _state;
};