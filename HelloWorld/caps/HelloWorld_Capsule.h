#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class HelloWorld_Capsule: public Capsule{
    public:
        HelloWorld_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr);

        int getId();
        void start();
        void handleMessage(Message message);
    private:
        void handleTimeout(TimeoutMessage message);

        int _id;
        TimerThread* _timerThreadPtr;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{
            S1,S2
        };
        State _state;
};