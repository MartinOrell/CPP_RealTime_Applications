#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include <chrono>
#include <stdexcept>
#include "SendMessage.h"

class CapsuleRunner;

class Clock_Capsule: public Capsule{
    public:
        Clock_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr, int speedMultiplier);
        int getId();
        void start();
        void handleMessage(Message message);

        void connectMain(int mainId);
        void connectSecond1Digit(int digitId);
        void connectSecond10Digit(int digitId);
        void connectMinute1Digit(int digitId);
        void connectMinute10Digit(int digitId);
        void connectHour1Digit(int digitId);
        void connectHour10Digit(int digitId);
        
    private:
        void sendRespondTimeMessage(int toId, std::string time);
        void sendIncMessage(int toId);
        void sendSetBaseMessage(int toId, int base);

        void handleTimeout(TimeoutMessage message);
        void handleMessage(CarryMessage inMessage);
        void handleRequestTimeMessage();

        RespondDigitMessage invokeRequestDigitMessage(int toId);

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
        MessageHandler<SendMessage>* _messageHandlerPtr;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{SecondTicker, Second10Ticker, MinuteTicker, Minute10Ticker, HourTicker};
        State _state;
};