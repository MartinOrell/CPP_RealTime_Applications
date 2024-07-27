#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Message.h"
#include "TimerThread.h"
#include "TrafficLight_Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(TimerThread*, MessageHandler<Message>*);
        void run();
    private:
        TrafficLight_Capsule _trafficLight;
        MessageHandler<Message>* _messageHandlerPtr;
};