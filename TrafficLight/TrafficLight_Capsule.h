#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class TrafficLight_Capsule{
    public:
        TrafficLight_Capsule(int id, MessageHandler<Message>*messageHandlerPtr, TimerThread* timerThreadPtr);
        void start();
        void handleTimeout(TimeoutMessage message);
    private:
        int _id;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{
            Red, Green, Yellow
        };
        State _state;
};