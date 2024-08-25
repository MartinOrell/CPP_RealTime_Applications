#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Main_Capsule: public mrt::Capsule{
    public:
        Main_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId() override;
        void start() override;
        void handleMessage(const mrt::Message& message) override;
        
    private:

        void handleRepeatTimerTimeout(int timeouts);
        void handleEndTimerTimeout();

        int _id;
        int _endTimerId;
        int _updateTimerId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        int _count;
};