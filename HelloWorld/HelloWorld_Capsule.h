#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class HelloWorld_Capsule{
    public:
        HelloWorld_Capsule(int id, MessageHandler<Message>*messageHandlerPtr, TimerThread* timerThreadPtr);
        void start();
        void handleTimeout(TimeoutMessage message);
    private:
        int _id;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{
            S1,S2
        };
        State _state;
};