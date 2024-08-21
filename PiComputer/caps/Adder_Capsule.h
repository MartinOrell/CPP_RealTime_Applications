#pragma once

#include "Capsule.h"

#include <iostream>
#include <math.h>
#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"

namespace mrt{
    class CapsuleRunner;
}

class Adder_Capsule: public mrt::Capsule{
    public:
        Adder_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);
        
        void connectPiComputer(int piComputerId);
        void connectMultiplier(int multiplierId);
        
    private:
        void sendGetIncrementMessage(int toId, int remainingIterations);
        void sendComputeResultMessage(int toId, double result);

        void handleMessage(mrt::ComputeRequest message);
        void handleMessage(mrt::ReturnIncrement message);

        void printDouble(double p1, int inc);

        int _id;
        int _piComputerId;
        int _multiplierId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        int _remainingIterations = 4;
        double _result;
        
        enum State{Idle, Computing};
        State _state;
};