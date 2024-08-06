#pragma once

#include <variant>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(int id);
        void addCapsule(std::unique_ptr<Capsule>);
        void run();
        void stop();
        void sendMessage(SendMessage message);
        Message invokeMessage(SendMessage request);
        int informIn(int, std::chrono::steady_clock::duration);
        int informEvery(int, std::chrono::steady_clock::duration);
        void cancelTimer(int);
    private:
        bool handleMessage(SendMessage message);
        bool handleMessageToMe(Message message);
        void handleTimeout(std::chrono::steady_clock::time_point now, std::vector<Timer>::iterator nextTimeout);

        void mergeOrSendTimeoutMessage(int toId, int timerId, int timeouts);

        int _id;
        MessageHandler _messageHandler;
        std::vector<std::unique_ptr<Capsule>> _capsules;
        std::vector<Timer> _timers;
    public:
        int _nextTimerId;
};