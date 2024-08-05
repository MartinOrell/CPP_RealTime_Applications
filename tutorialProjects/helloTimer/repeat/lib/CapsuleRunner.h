#pragma once

#include <variant>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(int id, MessageHandler*, std::vector<std::unique_ptr<Capsule>>*);
        void run();
        void stop();
        Message invokeMessage(SendMessage request);
    private:
        bool handleMessage(SendMessage message);

        int _id;
        MessageHandler* _messageHandlerPtr;
        std::vector<std::unique_ptr<Capsule>>* _capsulesPtr;
};