#pragma once

#include <variant>
#include <string>

struct TimeoutMessage{
    int timerId;
    int timeouts;
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
    VoidMessage,
    ComputeRequest,
    ComputeResult,
    ReturnIncrement,
    GetIncrement
    > Message;