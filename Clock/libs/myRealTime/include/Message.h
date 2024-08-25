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
        
}