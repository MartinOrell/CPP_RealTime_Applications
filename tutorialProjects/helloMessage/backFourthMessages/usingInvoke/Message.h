#pragma once

#include <variant>

struct Request{
    int toId;
    int value;
};

struct Response{
    int toId;
    int value;
};

enum RunInstruction{EndMessage};

typedef std::variant<Request, Response, RunInstruction> Message;