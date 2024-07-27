#pragma once

#include <iostream>
#include "Message.h"
#include <chrono>
#include "MessageHandler.h"

class PiComputer_Capsule{
    public:
        PiComputer_Capsule(MessageHandler<Message>*messageHandlerPtr);
        void start();
        void handleMessage(ComputeResult message);
    private:
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{WaitForComputation, Finished};
        State _state;
};