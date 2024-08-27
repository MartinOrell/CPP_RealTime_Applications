#include "Adder_Capsule.h"

#include "CapsuleRunner.h"

#include <iostream>
#include <math.h>

Adder_Capsule::Adder_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Adder_Capsule::getId(){
    return _id;
}

void Adder_Capsule::start(){
    _state = Idle;
}

void Adder_Capsule::receiveMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::ComputeRequest>(message)){
        handleMessage(std::get<mrt::ComputeRequest>(message));
    }
    else if(std::holds_alternative<mrt::ReturnIncrement>(message)){
        handleMessage(std::get<mrt::ReturnIncrement>(message));
    }
    else{
        throw std::invalid_argument("Adder_Capsule unable to handle that message");
    }
}

void Adder_Capsule::connectPiComputer(int piComputerId){
    _piComputerId = piComputerId;
}

void Adder_Capsule::connectMultiplier(int multiplierId){
    _multiplierId = multiplierId;
}

void Adder_Capsule::sendGetIncrementMessage(int toId, int remainingIterations){
    mrt::GetIncrement outMessage;
    outMessage.remainingIterations = remainingIterations;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Adder_Capsule::sendComputeResultMessage(int toId, double result){
    mrt::ComputeResult outMessage;
    outMessage.result = result;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Adder_Capsule::handleMessage(const mrt::ComputeRequest& inMessage){
    _state = Computing;
    _remainingIterations = inMessage.noOfIterations-1;
    sendGetIncrementMessage(_multiplierId, _remainingIterations);
}

void Adder_Capsule::handleMessage(const mrt::ReturnIncrement& inMessage){
    double inc = inMessage.inc;
    printDouble(inc, _remainingIterations);
    _result+=inc;
    if(_remainingIterations == 0){
        _state = Idle;
        _result = std::sqrt(12) * _result;
        sendComputeResultMessage(_piComputerId,_result);
    }
    else{
        _state = Computing;
        _remainingIterations--;
        sendGetIncrementMessage(_multiplierId, _remainingIterations);
    }
}

void Adder_Capsule::printDouble(double p1, int inc) {
    std::cout << "double " << p1 << " int " << inc << std::endl;
}