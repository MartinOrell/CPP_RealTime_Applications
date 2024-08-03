#pragma once

#include <variant>
#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(MessageHandler<SendMessage>*, std::vector<std::unique_ptr<Capsule>>*);
        void run();
        Message invokeMessage(SendMessage request);
    private:
        bool handleMessage(SendMessage message);

        MessageHandler<SendMessage>* _messageHandlerPtr;
        std::vector<std::unique_ptr<Capsule>>* _capsulesPtr;
};