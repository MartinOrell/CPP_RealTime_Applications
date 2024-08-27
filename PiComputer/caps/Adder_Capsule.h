#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
    class MessageHandler;
}

class Adder_Capsule: public mrt::Capsule{
    public:
        Adder_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId() override;
        void start() override;
        void receiveMessage(const mrt::Message&) override;
        
        void connectPiComputer(int piComputerId);
        void connectMultiplier(int multiplierId);
        
    private:
        void sendGetIncrementMessage(int toId, int remainingIterations);
        void sendComputeResultMessage(int toId, double result);

        void handleMessage(const mrt::ComputeRequest&);
        void handleMessage(const mrt::ReturnIncrement&);

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