#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class HelloTimer_Capsule{
    public:
        HelloTimer_Capsule(int id, MessageHandler<Message>*messageHandlerPtr, TimerThread* timerThreadPtr);
        void start();
        void handleTimeout(TimeoutMessage message);
    private:
        int _id;
        int _endTimerId;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{
            Running,End
        };
        State _state;
};