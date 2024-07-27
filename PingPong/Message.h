#pragma once

#include <variant>

struct TimeoutMessage{
    int toId;
    int timerId;
};

struct MessageToPing{
    int toId;
};

struct MessageToPong{
    int toId;
    int count;
};

typedef std::variant<TimeoutMessage, MessageToPing, MessageToPong> Message;