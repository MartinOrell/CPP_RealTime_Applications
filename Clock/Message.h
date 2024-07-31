#pragma once

#include <variant>
#include <string>

struct TimeoutMessage{
    int toId;
    int timerId;
    int timeouts;
};

enum VoidMessage{RequestTimeMessage, EndMessage};

struct RespondTimeMessage{
    std::string time;
};

struct RequestDigitMessage{
    int toId;
};

struct RespondDigitMessage{
    int fromId;
    int value;
};

struct IncMessage{
    int toId;
};

struct CarryMessage{
    int fromId;
};

struct SetBaseMessage{
    int toId;
    int base;
};

typedef std::variant<
    TimeoutMessage,
    VoidMessage,
    RespondTimeMessage,
    RequestDigitMessage,
    RespondDigitMessage,
    IncMessage,
    CarryMessage,
    SetBaseMessage
    > Message;

struct SendMessage{
    int toId;
    Message message;
};