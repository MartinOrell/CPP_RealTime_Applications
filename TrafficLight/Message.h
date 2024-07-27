#pragma once

#include <variant>

struct TimeoutMessage{
    int toId;
    int timerId;
};

typedef std::variant<TimeoutMessage> Message;