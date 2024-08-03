#pragma once

#include "Capsule.h"

#include <iostream>
#include "Message.h"
#include <chrono>
#include "MessageHandler.h"

class CapsuleRunner;

class PiComputer_Capsule: public Capsule{
    public:
        PiComputer_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connectAdder(int adderId);

    private:
        void sendComputeRequest(int toId, int noOfIterations);

        void handleMessage(ComputeResult message);
        
        int _id;
        int _adderId;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{WaitForComputation, Finished};
        State _state;
};