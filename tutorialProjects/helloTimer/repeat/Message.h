#pragma once

#include <variant>

struct TimeoutMessage{
    int timerId;
    int timeouts;
};

enum RunInstruction{EndMessage};

typedef std::variant<TimeoutMessage, RunInstruction> Message;

struct SendMessage{
    int toId;
    Message message;
};