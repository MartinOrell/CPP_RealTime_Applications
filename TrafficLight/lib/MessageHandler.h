#pragma once

#include <mutex>
#include <vector>
#include <cassert>

template <typename T>
class MessageHandler{
    public:
        MessageHandler();
        void sendMessage(T);
        T receiveMessage();
        bool hasMessage();
        void waitForMessage();
        bool waitForMessageUntil(std::chrono::steady_clock::time_point);
        void stop();
    private:
        std::mutex _mutex;
        std::vector<T> _messageStack;
        std::timed_mutex _waitForMessageMutex;
};

#include "MessageHandler.tpp"