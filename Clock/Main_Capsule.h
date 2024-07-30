#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class Main_Capsule{
    public:
        Main_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr, std::chrono::steady_clock::duration timeoutTime, int fps);
        int getId();
        void connect(int clockId);
        void start();
        void handleTimeout(TimeoutMessage message);
        void handleMessage(RespondTimeMessage message);
    private:
        int _id;
        int _clockId;
        std::chrono::steady_clock::duration _timeoutTime;
        int _endTimerId;
        std::chrono::steady_clock::duration _updateTime;
        int _updateTimerId;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{Running, WaitForTimeResponse, End};
        State _state;
};