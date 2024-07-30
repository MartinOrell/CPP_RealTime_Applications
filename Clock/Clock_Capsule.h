#pragma once

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class Clock_Capsule{
    public:
        Clock_Capsule(int id, MessageHandler<Message>*messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr, int speedMultiplier);
        int getId();
        void connectMain(int mainId);
        void connectSecond1Digit(int digitId);
        void connectSecond10Digit(int digitId);
        void connectMinute1Digit(int digitId);
        void connectMinute10Digit(int digitId);
        void connectHour1Digit(int digitId);
        void connectHour10Digit(int digitId);
        
        void start();
        void handleTimeout(TimeoutMessage message);
        void handleMessage(CarryMessage inMessage);
        void handleRequestTimeMessage();
    private:
        int _id;
        int _mainId;
        int _second1DigitCapsuleId;
        int _second10DigitCapsuleId;
        int _minute1DigitCapsuleId;
        int _minute10DigitCapsuleId;
        int _hour1DigitCapsuleId;
        int _hour10DigitCapsuleId;
        std::chrono::steady_clock::duration _tickPeriod;
        int _tickerId;
        TimerThread* _timerThreadPtr;
        MessageHandler<Message>* _messageHandlerPtr;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{SecondTicker, Second10Ticker, MinuteTicker, Minute10Ticker, HourTicker};
        State _state;
};