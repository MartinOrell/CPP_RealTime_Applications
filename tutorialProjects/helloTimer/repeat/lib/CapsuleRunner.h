#pragma once

#include <variant>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(int id, MessageHandler*, std::vector<std::unique_ptr<Capsule>>*);
        void run();
        void stop();
        Message invokeMessage(SendMessage request);
        int informIn(int, std::chrono::steady_clock::duration);
        int informEvery(int, std::chrono::steady_clock::duration);
        void cancelTimer(int);
    private:
        bool handleMessage(SendMessage message);

        void mergeOrSendTimeoutMessage(int toId, int timerId, int timeouts);

        int _id;
        MessageHandler* _messageHandlerPtr;
        std::vector<std::unique_ptr<Capsule>>* _capsulesPtr;
        std::vector<Timer> _timers;
    public:
        int _nextTimerId;
};