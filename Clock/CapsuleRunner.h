#pragma once

#include <variant>
#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "Main_Capsule.h"
#include "Clock_Capsule.h"
#include "Digit_Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(TimerThread*, MessageHandler<Message>*, std::chrono::steady_clock::duration timeoutTime, int fps, int speedMultiplier);
        void run();
        Message invokeMessage(Message request);
    private:
        int _nextCapsuleId;
        Main_Capsule _main;
        Clock_Capsule _clock;
        Digit_Capsule _second1Digit;
        Digit_Capsule _second10Digit;
        Digit_Capsule _minute1Digit;
        Digit_Capsule _minute10Digit;
        Digit_Capsule _hour1Digit;
        Digit_Capsule _hour10Digit;
        MessageHandler<Message>* _messageHandlerPtr;
};