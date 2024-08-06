#pragma once

#include <variant>
#include <string>
#include "Timer.h"

struct TimeoutMessage{
    int timerId;
    int timeouts;
};

struct CancelTimer{
    int id;
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
    Timer, //defined in Timer.h
    CancelTimer,
    VoidMessage,
    RespondTimeMessage,
    RespondDigitMessage,
    CarryMessage,
    SetBaseMessage
    > Message;