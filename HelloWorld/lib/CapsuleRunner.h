#pragma once

#include <variant>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(int id, MessageHandler<SendMessage>*, std::vector<std::unique_ptr<Capsule>>*);
        void run();
        void stop();
        Message invokeMessage(SendMessage request);
    private:
        bool handleMessage(SendMessage message);

        int _id;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        std::vector<std::unique_ptr<Capsule>>* _capsulesPtr;
};