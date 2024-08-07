#pragma once

#include <variant>
#include "Timer.h"

struct TimeoutMessage{
    int timerId;
    int timeouts;
};


struct CancelTimer{
    int id;
};

enum VoidMessage{EndMessage, MessageToPing};

struct MessageToPong{
    int count;
};

typedef std::variant<
    TimeoutMessage,
    Timer, //defined in Timer.h
    CancelTimer,
    VoidMessage,
    MessageToPong
    > Message;