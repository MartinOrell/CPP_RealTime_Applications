#pragma once

#include "Capsule.h"

#include <iostream>
#include "Message.h"
#include <chrono>
#include "MessageHandler.h"

class PiComputer_Capsule: public Capsule{
    public:
        PiComputer_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connectAdder(int adderId);
    private:
        void sendEndMessage();
        void sendComputeRequest(int toId, int noOfIterations);

        void handleMessage(ComputeResult message);
        int _id;
        int _adderId;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        enum State{WaitForComputation, Finished};
        State _state;
};