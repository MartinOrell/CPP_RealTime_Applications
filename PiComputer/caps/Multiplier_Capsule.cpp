#include "Multiplier_Capsule.h"

#include "CapsuleRunner.h"

#include <cmath>

Multiplier_Capsule::Multiplier_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Multiplier_Capsule::getId(){
    return _id;
}

void Multiplier_Capsule::start(){}

void Multiplier_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::GetIncrement>(message)){
        handleMessage(std::get<mrt::GetIncrement>(message));
    }
    else{
        throw std::invalid_argument("Multiplier_Capsule unable to handle that message");
    }
}

void Multiplier_Capsule::connectAdder(int adderId){
    _adderId = adderId;
}

void Multiplier_Capsule::sendReturnIncrementMessage(int toId, double inc){
    mrt::ReturnIncrement outMessage;
    outMessage.inc = inc;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Multiplier_Capsule::handleMessage(const mrt::GetIncrement& inMessage){
    int k = inMessage.remainingIterations;
    double inc = std::pow(-3, -k) / (2 * k + 1);
    sendReturnIncrementMessage(_adderId, inc);
}