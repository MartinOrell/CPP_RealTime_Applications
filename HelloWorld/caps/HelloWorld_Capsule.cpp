#include "HelloWorld_Capsule.h"

#include "CapsuleRunner.h"

#include <chrono>
#include <stdexcept>
#include <iostream>

HelloWorld_Capsule::HelloWorld_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
}

int HelloWorld_Capsule::getId(){
    return _id;
}

void HelloWorld_Capsule::start(){
    _state = S1;
    _timerRunnerPtr->informIn(_id, std::chrono::seconds(1));
}

void HelloWorld_Capsule::receiveMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        receiveTimeout(std::get<mrt::TimeoutMessage>(message));
        return;
    }
    
    std::string errorMsg =
        "HelloWorld_Capsule[" +
        std::to_string(_id) +
        "] unable to receive Message[" +
        std::to_string(message.index()) +
        "]";
        throw std::invalid_argument(errorMsg);
}

void HelloWorld_Capsule::receiveTimeout(const mrt::TimeoutMessage& timeoutMessage){
    hello();
}

void HelloWorld_Capsule::hello(){
    if(_state != State::S1){
        return;
    }
    std::cout << "Hello World!" << std::endl;
    _capsuleRunnerPtr->stop();
    _state = S2;
}