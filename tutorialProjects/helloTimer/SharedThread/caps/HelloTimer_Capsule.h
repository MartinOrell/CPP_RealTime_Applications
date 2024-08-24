#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"
#include <chrono>

namespace mrt{
    class CapsuleRunner;
}

class HelloTimer_Capsule: public mrt::Capsule{
    public:
        HelloTimer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, std::chrono::steady_clock::duration updateTime, std::chrono::steady_clock::duration runDuration);
        int getId();
        void start();
        
        void handleMessage(const mrt::Message& message);
    private:
        void handleTimeout(const mrt::TimeoutMessage& message);

        void update(int timeouts);
        void end();

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{Running, End};
        State _state;

        int _updateTimerId;
        std::chrono::steady_clock::duration _updateTime;
        int _endTimerId;
        std::chrono::steady_clock::duration _runDuration;
};