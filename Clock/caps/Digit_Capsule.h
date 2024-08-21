#pragma once

#include "Capsule.h"

#include "Message.h"
#include <stdexcept>

namespace mrt{
    class CapsuleRunner;
}

class Digit_Capsule: public mrt::Capsule{
    public:
        Digit_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);
        mrt::Message handleInvokeMessage(mrt::Message request);

        void connect(int clockId);
        
    private:
        void sendCarryMessage(int toId);

        void handleIncMessage();
        void handleMessage(mrt::SetBaseMessage inMessage);
        
        mrt::Message handleInvokeRequestDigitMessage();

        int _id;
        int _clockId;
        int _base;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};
        State _state;
};