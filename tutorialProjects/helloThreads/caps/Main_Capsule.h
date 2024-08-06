#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <chrono>
#include <stdexcept>


class CapsuleRunner;

class Main_Capsule: public Capsule{
    public:
        Main_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
    private:

        void handleRepeatTimerTimeout(int timeouts);
        void handleEndTimerTimeout();

        int _id;
        int _endTimerId;
        int _updateTimerId;
        CapsuleRunner* _capsuleRunnerPtr;
        CapsuleRunner* _timerRunnerPtr;
        int _count;
};