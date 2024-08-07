#include "Adder_Capsule.h"
#include "CapsuleRunner.h"

Adder_Capsule::Adder_Capsule(int id, CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Adder_Capsule::getId(){
    return _id;
}

void Adder_Capsule::start(){
    _state = Idle;
}

void Adder_Capsule::handleMessage(Message message){
    if(std::holds_alternative<ComputeRequest>(message)){
        handleMessage(std::get<ComputeRequest>(message));
    }
    else if(std::holds_alternative<ReturnIncrement>(message)){
        handleMessage(std::get<ReturnIncrement>(message));
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
    GetIncrement outMessage;
    outMessage.remainingIterations = remainingIterations;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Adder_Capsule::sendComputeResultMessage(int toId, double result){
    ComputeResult outMessage;
    outMessage.result = result;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Adder_Capsule::handleMessage(ComputeRequest inMessage){
    _state = Computing;
    _remainingIterations = inMessage.noOfIterations-1;
    sendGetIncrementMessage(_multiplierId, _remainingIterations);
}

void Adder_Capsule::handleMessage(ReturnIncrement inMessage){
    double inc = inMessage.inc;
    printDouble(inc, _remainingIterations);
    _result+=inc;
    if(_remainingIterations == 0){
        _state = Idle;
        _result = sqrt(12) * _result;
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