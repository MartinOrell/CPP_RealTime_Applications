#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class HelloTimer_Capsule: public mrt::Capsule{
    public:
        HelloTimer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId() override;
        void start() override;
        void handleMessage(const mrt::Message& message) override;
    private:
        void handleTimeout(const mrt::TimeoutMessage& message);

        int _id;
        int _repeatTimerId;
        int _endTimerId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{Running, End};
        State _state;
};