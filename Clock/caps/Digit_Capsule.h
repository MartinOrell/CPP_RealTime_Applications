#pragma once

#include "Capsule.h"

#include "Message.h"
#include <stdexcept>

class CapsuleRunner;

class Digit_Capsule: public Capsule{
    public:
        Digit_Capsule(int id, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        Message handleInvokeMessage(Message request);

        void connect(int clockId);
        
    private:
        void sendCarryMessage(int toId);

        void handleIncMessage();
        void handleMessage(SetBaseMessage inMessage);
        
        Message handleInvokeRequestDigitMessage();

        int _id;
        int _clockId;
        int _base;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};
        State _state;
};