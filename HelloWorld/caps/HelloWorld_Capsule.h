#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class HelloWorld_Capsule: public Capsule{
    public:
        HelloWorld_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
    private:
        void handleTimeout(TimeoutMessage message);

        int _id;
        CapsuleRunner* _capsuleRunnerPtr;
        CapsuleRunner* _timerRunnerPtr;
        enum State{
            S1,S2
        };
        State _state;
};