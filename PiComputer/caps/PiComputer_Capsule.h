#pragma once

#include "Capsule.h"

#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include <chrono>

namespace mrt{
    class CapsuleRunner;
}

class PiComputer_Capsule: public mrt::Capsule{
    public:
        PiComputer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);
        
        void connectAdder(int adderId);

    private:
        void sendComputeRequest(int toId, int noOfIterations);

        void handleMessage(mrt::ComputeResult message);
        
        int _id;
        int _adderId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{WaitForComputation, Finished};
        State _state;
};