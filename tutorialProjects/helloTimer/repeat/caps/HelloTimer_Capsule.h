#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class HelloTimer_Capsule: public Capsule{
    public:
        HelloTimer_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
    private:
        void handleTimeout(TimeoutMessage message);

        int _id;
        int _repeatTimerId;
        int _endTimerId;
        TimerThread* _timerThreadPtr;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{Running, End};
        State _state;
};