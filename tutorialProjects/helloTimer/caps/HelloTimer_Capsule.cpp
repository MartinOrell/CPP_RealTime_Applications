#include "HelloTimer_Capsule.h"
#include "CapsuleRunner.h"

HelloTimer_Capsule::HelloTimer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
}

int HelloTimer_Capsule::getId(){
    return _id;
}

void HelloTimer_Capsule::start(){
    _state = Running;
    std::cout << "Hello World!" << std::endl;
    _repeatTimerId = _timerRunnerPtr->informEvery(_id, std::chrono::milliseconds(500));
    _endTimerId = _timerRunnerPtr->informIn(_id, std::chrono::seconds(3));
}

void HelloTimer_Capsule::handleMessage(mrt::Message message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        handleTimeout(std::get<mrt::TimeoutMessage>(message));
    }
    else{
        throw std::invalid_argument("HelloTimer_Capsule unable to handle message with type id: " + std::to_string(message.index()));
    }
}

void HelloTimer_Capsule::handleTimeout(mrt::TimeoutMessage timeoutMessage){

    if(timeoutMessage.timerId == _repeatTimerId && _state == Running){
        for(int i = 0; i < timeoutMessage.timeouts; i++){
            std::cout << "Hello World!" << std::endl;
        }
    }
    else if(timeoutMessage.timerId == _endTimerId && _state == Running){
        _state = End;
        std::cout << "Goodbye World!" << std::endl;
        _timerRunnerPtr->cancelTimer(_repeatTimerId);
        _capsuleRunnerPtr->stop();
    }
    else{
        throw std::out_of_range("HelloTimer does not support timeout with id " + std::to_string(timeoutMessage.timerId) + " in state " + std::to_string(_state));
    }
}