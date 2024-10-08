#pragma once

#include <variant>
#include "Timer.h"

namespace mrt{

    struct TimeoutMessage{
        int timerId;
        int timeouts;
    };

    struct CancelTimer{
        int timerId;
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
        
}