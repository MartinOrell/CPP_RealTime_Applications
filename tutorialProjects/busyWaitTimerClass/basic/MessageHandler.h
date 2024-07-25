#pragma once

#include <mutex>
#include <vector>

template <typename T>
class MessageHandler{
    public:
        MessageHandler();
        void addMessage(T);
        bool hasMessage();
        T popMessage();
    private:
        std::mutex _mutex;
        std::vector<T> _messageStack;
};

#include "MessageHandler.tpp"