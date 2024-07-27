#pragma once

#include <variant>

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

enum RunInstruction{End};

typedef std::variant<ComputeRequest, ComputeResult, ReturnIncrement, GetIncrement, RunInstruction> Message;