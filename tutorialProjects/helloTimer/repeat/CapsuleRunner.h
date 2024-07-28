#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Message.h"
#include "TimerThread.h"
#include "HelloTimer_Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(TimerThread*, MessageHandler<Message>*);
        void run();
    private:
        HelloTimer_Capsule _helloTimer;
        MessageHandler<Message>* _messageHandlerPtr;
};