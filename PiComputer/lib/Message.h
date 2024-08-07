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

enum VoidMessage{EndMessage};

struct ComputeRequest{
    int noOfIterations;
};

struct ComputeResult{
    double result;
};

struct ReturnIncrement{
    double inc;
};

struct GetIncrement{
    int remainingIterations;
};

typedef std::variant<
    TimeoutMessage,
    Timer, //defined in Timer.h
    CancelTimer,
    VoidMessage,
    ComputeRequest,
    ComputeResult,
    ReturnIncrement,
    GetIncrement
    > Message;