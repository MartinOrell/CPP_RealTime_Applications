#pragma once

#include <variant>

struct TimeoutMessage{
    int toId;
    int timerId;
};

enum RunInstruction{End};

typedef std::variant<TimeoutMessage, RunInstruction> Message;