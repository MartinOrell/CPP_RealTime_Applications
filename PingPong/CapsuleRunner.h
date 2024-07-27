#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Ping_Capsule.h"
#include "Pong_Capsule.h"
#include "Message.h"
#include "TimerThread.h"

class CapsuleRunner{
    public:
        CapsuleRunner(TimerThread*, MessageHandler<Message>*);
        void run();
    private:
        Ping_Capsule _pinger;
        Pong_Capsule _ponger;
        MessageHandler<Message>* _messageHandlerPtr;
};