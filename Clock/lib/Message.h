#pragma once

#include <variant>
#include <string>

struct TimeoutMessage{
    int timerId;
    int timeouts;
};

enum VoidMessage{RequestTimeMessage, RequestDigitMessage, IncMessage, EndMessage};

struct RespondTimeMessage{
    std::string time;
};

struct RespondDigitMessage{
    int fromId;
    int value;
};

struct CarryMessage{
    int fromId;
};

struct SetBaseMessage{
    int base;
};

typedef std::variant<
    TimeoutMessage,
    VoidMessage,
    RespondTimeMessage,
    RespondDigitMessage,
    CarryMessage,
    SetBaseMessage
    > Message;