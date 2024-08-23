#include "PiComputer_Capsule.h"

#include "CapsuleRunner.h"

#include <iostream>

PiComputer_Capsule::PiComputer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int PiComputer_Capsule::getId(){
    return _id;
}

void PiComputer_Capsule::start(){
    _state = WaitForComputation;
    int noOfIterations = 100;
    std::cout << "Starting computation of pi using the Madhavas formula with " << noOfIterations << " iterations" << std::endl;
    sendComputeRequest(_adderId, noOfIterations);
}

void PiComputer_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::ComputeResult>(message)){
        handleMessage(std::get<mrt::ComputeResult>(message));
    }
    else{
        throw std::invalid_argument("PiComputer_Capsule unable to handle that message");
    }
}

void PiComputer_Capsule::connectAdder(int adderId){
    _adderId = adderId;
}

void PiComputer_Capsule::sendComputeRequest(int toId, int noOfIterations){
    mrt::ComputeRequest outMessage;
    outMessage.noOfIterations = noOfIterations;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void PiComputer_Capsule::handleMessage(const mrt::ComputeResult& message){
    _state = Finished;
    std::cout << "Result is : " << std::setprecision(20) << std::fixed << message.result << std::endl;
    _capsuleRunnerPtr->stop();
}