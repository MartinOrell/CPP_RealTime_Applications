#pragma once

#include <mutex>
#include <vector>
#include <cassert>
#include <algorithm>
#include "SendMessage.h"

class MessageHandler{
    public:
        MessageHandler();
        void sendMessage(SendMessage);
        void mergeOrSendMessage(SendMessage);
        SendMessage receiveMessage();
        bool hasMessage();
        void waitForMessage();
        bool waitForMessageUntil(std::chrono::steady_clock::time_point);
        void stop();
    private:
        std::mutex _mutex;
        std::vector<SendMessage> _messageStack;
        std::timed_mutex _waitForMessageMutex;
};