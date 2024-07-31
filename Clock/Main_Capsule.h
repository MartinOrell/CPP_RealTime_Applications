#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class Main_Capsule: public Capsule{
    public:
        Main_Capsule(int id, MessageHandler<SendMessage>* messageHandlerPtr, TimerThread* timerThreadPtr, std::chrono::steady_clock::duration timeoutTime, int fps);
        
        int getId();
        void start();
        void handleMessage(Message message);

        void connect(int clockId);
        
    private:

        void handleTimeout(TimeoutMessage message);
        void handleMessage(RespondTimeMessage message);

        int _id;
        int _clockId;
        std::chrono::steady_clock::duration _timeoutTime;
        int _endTimerId;
        std::chrono::steady_clock::duration _updateTime;
        int _updateTimerId;
        TimerThread* _timerThreadPtr;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        enum State{Running, WaitForTimeResponse, End};
        State _state;
};