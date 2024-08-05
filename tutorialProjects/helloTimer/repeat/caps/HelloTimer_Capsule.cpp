#include "HelloTimer_Capsule.h"
#include "CapsuleRunner.h"

HelloTimer_Capsule::HelloTimer_Capsule(int id, MessageHandler*messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
    _capsuleRunnerPtr = _capsuleRunnerPtr;
}

int HelloTimer_Capsule::getId(){
    return _id;
}

void HelloTimer_Capsule::start(){
    _state = Running;
    std::cout << "Hello World!" << std::endl;
    _repeatTimerId = _timerThreadPtr->informEvery(_id, std::chrono::milliseconds(500));
    _endTimerId = _timerThreadPtr->informIn(_id, std::chrono::seconds(3));
}

void HelloTimer_Capsule::handleMessage(Message message){
    if(std::holds_alternative<TimeoutMessage>(message)){
        handleTimeout(std::get<TimeoutMessage>(message));
    }
    else{
        throw std::invalid_argument("HelloTimer_Capsule unable to handle that message");
    }
}

void HelloTimer_Capsule::handleTimeout(TimeoutMessage timeoutMessage){

    if(timeoutMessage.timerId == _repeatTimerId && _state == Running){
        for(int i = 0; i < timeoutMessage.timeouts; i++){
            std::cout << "Hello World!" << std::endl;
        }
    }
    else if(timeoutMessage.timerId == _endTimerId && _state == Running){
        _state = End;
        std::cout << "Goodbye World!" << std::endl;
        _timerThreadPtr->cancelTimer(_repeatTimerId);
        _capsuleRunnerPtr->stop();
    }
    else{
        throw std::out_of_range("HelloTimer does not support timeout with id " + std::to_string(timeoutMessage.timerId) + " in state " + std::to_string(_state));
    }
}