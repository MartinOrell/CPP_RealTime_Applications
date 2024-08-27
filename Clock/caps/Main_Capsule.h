#pragma once

#include "Capsule.h"

#include <string>
#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Main_Capsule: public mrt::Capsule{
    public:
        Main_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, std::chrono::steady_clock::duration timeoutTime, int fps);
        int getId() override;
        void start() override;
        void receiveMessage(const mrt::Message&) override;

        void connect(int clockId);
        
    private:
        void sendRequestTimeMessage(int toId);

        void receiveTimeout(const mrt::TimeoutMessage&);
        void receiveMessage(const mrt::RespondTimeMessage&);

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