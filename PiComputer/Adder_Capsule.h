#pragma once

#include <iostream>
#include <math.h>
#include "Message.h"
#include "MessageHandler.h"

class Adder_Capsule{
    public:
        Adder_Capsule(MessageHandler<Message>*messageHandlerPtr);
        void start();
        void handleMessage(ComputeRequest message);
        void handleMessage(ReturnIncrement message);
    private:
        void printDouble(double p1, int inc);

        MessageHandler<Message>* _messageHandlerPtr;
        int _remainingIterations = 4;
        double _result;
        
        enum State{Idle, Computing};
        State _state;
};