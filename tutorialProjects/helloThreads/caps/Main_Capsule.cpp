#include "Main_Capsule.h"

#include "CapsuleRunner.h"

#include <chrono>
#include <stdexcept>
#include <string>
#include <iostream>

Main_Capsule::Main_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
    _count = 0;
}

int Main_Capsule::getId(){
    return _id;
}
        
void Main_Capsule::receiveMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        receiveTimeout(std::get<mrt::TimeoutMessage>(message));
        return;
    }

    std::string errorMsg =
        "Main_Capsule unable to handle Message[" +
        std::to_string(message.index()) +
        "]";
    throw std::invalid_argument(errorMsg);
}

void Main_Capsule::receiveTimeout(const mrt::TimeoutMessage& timeoutMessage){
    if(timeoutMessage.timerId == _updateTimerId){
        update(timeoutMessage.timeouts);
        return;
    }
    if(timeoutMessage.timerId == _endTimerId){
        end();
        return;
    }
    
    std::string errorMsg =
        "Main_Capsule unable to receive Timeout[" +
        std::to_string(timeoutMessage.timerId) +
        "]";
    throw std::invalid_argument(errorMsg);
}

void Main_Capsule::start(){
    std::cout << "Main: Start updateTimer every second\n";
    _updateTimerId = _timerRunnerPtr->informEvery(_id, std::chrono::seconds(1));
    _endTimerId = _timerRunnerPtr->informIn(_id, std::chrono::seconds(12));
}

void Main_Capsule::update(int timeouts){
    _count++;
    if(timeouts > 1){
        std::cout << "Main: Missed timeouts: " + std::to_string(timeouts-1) + "\n"; 
    }
    std::cout << "Main: Count: " + std::to_string(_count) + "\n";
}

void Main_Capsule::end(){
    _capsuleRunnerPtr->stop();
}