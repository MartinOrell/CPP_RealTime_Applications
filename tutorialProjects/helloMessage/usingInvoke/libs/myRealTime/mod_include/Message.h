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

    struct Request{
        int value;
    };

    struct Response{
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
        
}