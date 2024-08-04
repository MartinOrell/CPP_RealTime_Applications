#pragma once

#include "Message.h"
#include <variant>

class SendMessage{
    public:
        int toId;
        Message message;
        bool operator==(const SendMessage& rhs);
        void merge(SendMessage fromM);
};