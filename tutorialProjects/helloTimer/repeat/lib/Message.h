#pragma once

#include <variant>
#include <string>
#include <chrono>

struct TimeoutMessage{
    int timerId;
    int timeouts;
};

struct Timer{
    int id;
    int toId;
    std::chrono::steady_clock::time_point timeoutTime;
    bool isRepeating;
    std::chrono::steady_clock::duration interval;

    bool operator<(Timer a){
        return timeoutTime < a.timeoutTime;
    }
};

struct CancelTimer{
    int id;
};

enum VoidMessage{EndMessage};

typedef std::variant<
    TimeoutMessage,
    Timer,
    CancelTimer,
    VoidMessage
    > Message;