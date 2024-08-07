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

enum VoidMessage{EndMessage};

struct Request{
    int toId;
    int value;
};

struct Response{
    int toId;
    int value;
};

typedef std::variant<
    TimeoutMessage,
    Timer, //defined in Timer.h
    CancelTimer,
    VoidMessage,
    Request,
    Response
    > Message;