#pragma once

#include "Capsule.h"

#include <iostream>
#include <math.h>
#include "Message.h"
#include "MessageHandler.h"

class Adder_Capsule: public Capsule{
    public:
        Adder_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr);

        int getId();
        void start();
        void handleMessage(Message message);
        
        void connectPiComputer(int piComputerId);
        void connectMultiplier(int multiplierId);
    private:
        void sendGetIncrementMessage(int toId, int remainingIterations);
        void sendComputeResultMessage(int toId, double result);

        void handleMessage(ComputeRequest message);
        void handleMessage(ReturnIncrement message);

        void printDouble(double p1, int inc);

        int _id;
        int _piComputerId;
        int _multiplierId;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        int _remainingIterations = 4;
        double _result;
        
        enum State{Idle, Computing};
        State _state;
};