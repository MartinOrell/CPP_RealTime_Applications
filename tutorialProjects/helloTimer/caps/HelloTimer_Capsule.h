#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "MessageHandler.h"
#include <chrono>
#include <stdexcept>

namespace mrt{
    class CapsuleRunner;
}

class HelloTimer_Capsule: public mrt::Capsule{
    public:
        HelloTimer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);
    private:
        void handleTimeout(mrt::TimeoutMessage message);

        int _id;
        int _repeatTimerId;
        int _endTimerId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{Running, End};
        State _state;
};