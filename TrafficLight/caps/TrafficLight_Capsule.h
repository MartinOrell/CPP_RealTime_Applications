#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class TrafficLight_Capsule: public Capsule{
    public:
        TrafficLight_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr, TimerThread* timerThreadPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
    private:
        void handleTimeout(TimeoutMessage message);

        int _id;
        TimerThread* _timerThreadPtr;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        enum State{
            Red, Green, Yellow
        };
        State _state;
};