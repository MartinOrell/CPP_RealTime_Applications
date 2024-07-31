#pragma once

#include <variant>
#include <string>

struct TimeoutMessage{
    int toId;
    int timerId;
    int timeouts;
};

enum NoContentMessage{RequestTimeMessage, EndMessage};

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
    NoContentMessage,
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