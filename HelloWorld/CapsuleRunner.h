#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Message.h"
#include "TimerThread.h"
#include "HelloWorld_Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(TimerThread*, MessageHandler<Message>*);
        void run();
    private:
        HelloWorld_Capsule _helloWorld;
        MessageHandler<Message>* _messageHandlerPtr;
};