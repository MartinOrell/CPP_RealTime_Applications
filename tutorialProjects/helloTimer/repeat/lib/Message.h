#pragma once

#include <variant>
#include <string>

struct TimeoutMessage{
    int timerId;
    int timeouts;
};

enum VoidMessage{EndMessage};

typedef std::variant<
    TimeoutMessage,
    VoidMessage
    > Message;