#pragma once

#include <variant>

struct TimeoutMessage{
    int toId;
    int timerId;
    int timeouts;
};

enum RunInstruction{EndMessage};

typedef std::variant<TimeoutMessage, RunInstruction> Message;