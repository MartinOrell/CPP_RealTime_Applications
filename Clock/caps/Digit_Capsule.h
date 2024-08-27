#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Digit_Capsule: public mrt::Capsule{
    public:
        Digit_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId() override;
        void start() override;
        void receiveMessage(const mrt::Message&) override;
        mrt::Message receiveInvokeMessage(const mrt::Message&) override;

        void connect(int clockId);
        
    private:
        void sendCarryMessage(int toId);

        void receiveIncMessage();
        void receiveMessage(mrt::SetBaseMessage);
        
        mrt::Message receiveInvokeRequestDigitMessage();

        int _id;
        int _clockId;
        int _base;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};
        State _state;
};