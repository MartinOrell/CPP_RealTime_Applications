#pragma once

#include <variant>
#include <string>

struct TimeoutMessage{
    int timerId;
    int timeouts;
};

enum VoidMessage{EndMessage, MessageToPing};

struct MessageToPong{
    int count;
};

typedef std::variant<
    TimeoutMessage,
    VoidMessage,
    MessageToPong
    > Message;

struct SendMessage{
    int toId;
    Message message;
};