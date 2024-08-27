#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class PiComputer_Capsule: public mrt::Capsule{
    public:
        PiComputer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId() override;
        void start() override;
        void receiveMessage(const mrt::Message&) override;
        
        void connectAdder(int adderId);

    private:
        void sendComputeRequest(int toId, int noOfIterations);

        void handleMessage(const mrt::ComputeResult&);
        
        int _id;
        int _adderId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{WaitForComputation, Finished};
        State _state;
};