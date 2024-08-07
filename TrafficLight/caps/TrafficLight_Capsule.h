#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class TrafficLight_Capsule: public Capsule{
    public:
        TrafficLight_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
    private:
        void handleTimeout(TimeoutMessage message);

        int _id;
        CapsuleRunner* _capsuleRunnerPtr;
        CapsuleRunner* _timerRunnerPtr;
        enum State{Red, Green, Yellow};
        State _state;
};