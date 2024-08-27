#include "HelloTimer_Capsule.h"

#include "CapsuleRunner.h"

#include <stdexcept>
#include <iostream>

HelloTimer_Capsule::HelloTimer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, std::chrono::steady_clock::duration updateTime, std::chrono::steady_clock::duration runDuration)
: _id{id}
, _capsuleRunnerPtr{capsuleRunnerPtr}
, _timerRunnerPtr{timerRunnerPtr}
, _updateTime{updateTime}
, _runDuration{runDuration}{}

int HelloTimer_Capsule::getId(){
    return _id;
}

void HelloTimer_Capsule::receiveMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        receiveTimeout(std::get<mrt::TimeoutMessage>(message));
        return;
    }
    
    std::string errorMsg =
        "HelloTimer_Capsule[" +
        std::to_string(_id) + 
        "] unable to receive Message[" +
        std::to_string(message.index()) +
        "]";
    throw std::invalid_argument(errorMsg);
}

void HelloTimer_Capsule::receiveTimeout(const mrt::TimeoutMessage& timeoutMessage){

    if(timeoutMessage.timerId == _updateTimerId){
        update(timeoutMessage.timeouts);
        return;
    }
    if(timeoutMessage.timerId == _endTimerId){
        end();
        return;
    }
    
    std::string errorMsg =
        "HelloTimer_Capsule[" +
        std::to_string(_id) +
        "] can not receive timeout from Timer[" +
        std::to_string(timeoutMessage.timerId) +
        "]";
    throw std::invalid_argument(errorMsg);
}

void HelloTimer_Capsule::start(){
    std::cout << "Hello World!" << std::endl;
    _updateTimerId = _timerRunnerPtr->informEvery(_id, _updateTime);
    _endTimerId = _timerRunnerPtr->informIn(_id, _runDuration);
    _state = State::Running;
}

void HelloTimer_Capsule::update(int timeouts){
    if(_state != State::Running){
        return;
    }
    for(int i = 0; i < timeouts; i++){
        std::cout << "Hello World!" << std::endl;
    }
}

void HelloTimer_Capsule::end(){
    if(_state != State::Running){
        return;
    }
    std::cout << "Goodbye World!" << std::endl;
    _timerRunnerPtr->cancelTimer(_updateTimerId);
    _capsuleRunnerPtr->stop();
    _state = State::End;
}
