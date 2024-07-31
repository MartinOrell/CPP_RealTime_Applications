#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Message.h"
#include "TimerThread.h"
#include "HelloTimer_Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(TimerThread*, MessageHandler<SendMessage>*);
        void run();
    private:
        HelloTimer_Capsule _helloTimer;
        MessageHandler<SendMessage>* _messageHandlerPtr;
};