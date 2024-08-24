#include "HelloTimer_Capsule.h"

#include "CapsuleRunner.h"

#include <iostream>

HelloTimer_Capsule::HelloTimer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, std::chrono::steady_clock::duration updateTime, std::chrono::steady_clock::duration runDuration)
: _id{id}
, _capsuleRunnerPtr{capsuleRunnerPtr}
, _updateTime{updateTime}
, _runDuration{runDuration}{}

int HelloTimer_Capsule::getId(){
    return _id;
}

void HelloTimer_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        handleTimeout(std::get<mrt::TimeoutMessage>(message));
        return;
    }

    std::string errorMsg =
        "HelloTimer_Capsule unable to handle message with type id: " +
        std::to_string(message.index());
    throw std::invalid_argument(errorMsg);
}

void HelloTimer_Capsule::handleTimeout(const mrt::TimeoutMessage& timeoutMessage){
    if(timeoutMessage.timerId == _updateTimerId){
        update(timeoutMessage.timeouts);
        return;
    }
    if(timeoutMessage.timerId == _endTimerId){
        end();
        return;
    }

    std::string errorMsg =
        "HelloTimer_Capsule does not support timeout with id " +
        std::to_string(timeoutMessage.timerId);
    throw std::invalid_argument(errorMsg);
}

void HelloTimer_Capsule::start(){
    std::cout << "Hello World!" << std::endl;
    _updateTimerId = _capsuleRunnerPtr->informEvery(_id, _updateTime);
    _endTimerId = _capsuleRunnerPtr->informIn(_id, _runDuration);
    _state = State::Running;
}

void HelloTimer_Capsule::update(int timeouts){
    if(_state != State::Running){
        return;
    }
    std::cout << "Hello World!" << std::endl;
}

void HelloTimer_Capsule::end(){
    if(_state != State::Running){
        return;
    }
    std::cout << "Goodbye World" << std::endl;
    _capsuleRunnerPtr->cancelTimer(_updateTimerId);
    _capsuleRunnerPtr->stop();
    _state = State::End;
}