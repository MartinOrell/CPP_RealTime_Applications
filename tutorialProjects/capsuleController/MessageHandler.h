#pragma once

#include <mutex>
#include <vector>
#include <cassert>

template <typename T>
class MessageHandler{
    public:
        MessageHandler();
        void addMessage(T);
        bool hasMessage();
        void waitForMessage();
        bool waitForMessageUntil(std::chrono::steady_clock::time_point);
        T popMessage();
        void stop();
    private:
        std::mutex _mutex;
        std::vector<T> _messageStack;
        std::timed_mutex _waitForMessageMutex;
};

#include "MessageHandler.tpp"