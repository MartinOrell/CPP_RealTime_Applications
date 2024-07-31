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
        CapsuleRunner(MessageHandler<SendMessage>*, std::vector<std::unique_ptr<Capsule>>*);
        void run();
        Message invokeMessage(SendMessage request);
    private:
        MessageHandler<SendMessage>* _messageHandlerPtr;
        std::vector<std::unique_ptr<Capsule>>* _capsulesPtr;
};