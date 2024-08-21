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

class Main_Capsule: public mrt::Capsule{
    public:
        Main_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, std::chrono::steady_clock::duration timeoutTime, int fps);
        int getId();
        void start();
        void handleMessage(mrt::Message message);

        void connect(int clockId);
        
    private:
        void sendRequestTimeMessage(int toId);

        void handleTimeout(mrt::TimeoutMessage message);
        void handleMessage(mrt::RespondTimeMessage message);

        int _id;
        int _clockId;
        std::chrono::steady_clock::duration _timeoutTime;
        int _endTimerId;
        std::chrono::steady_clock::duration _updateTime;
        int _updateTimerId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{Running, WaitForTimeResponse, End};
        State _state;
};