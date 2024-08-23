#pragma once

#include "Capsule.h"

#include <string>
#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Clock_Capsule: public mrt::Capsule{
    public:
        Clock_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, int speedMultiplier);
        int getId();
        void start();
        void handleMessage(const mrt::Message& message);

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

        void handleTimeout(const mrt::TimeoutMessage& message);
        void handleMessage(const mrt::CarryMessage& inMessage);
        void handleRequestTimeMessage();

        mrt::RespondDigitMessage invokeRequestDigitMessage(int toId);

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
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        enum State{SecondTicker, Second10Ticker, MinuteTicker, Minute10Ticker, HourTicker};
        State _state;
};