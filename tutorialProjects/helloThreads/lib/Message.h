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

typedef std::variant<
    TimeoutMessage,
    Timer, //defined in Timer.h
    CancelTimer,
    VoidMessage
    > Message;