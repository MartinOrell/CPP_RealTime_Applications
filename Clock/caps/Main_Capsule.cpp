#include "Main_Capsule.h"

#include "CapsuleRunner.h"

#include <chrono>
#include <stdexcept>
#include <cassert>
#include <iostream>

Main_Capsule::Main_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, std::chrono::steady_clock::duration timeoutTime, int fps){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
    _timeoutTime = timeoutTime;
    _updateTime = std::chrono::milliseconds(1000/fps);
    if(_updateTime <= std::chrono::milliseconds(0)){
        throw std::range_error("updateTime is too low, try a lower fps");
    }
}

int Main_Capsule::getId(){
    return _id;
}

void Main_Capsule::receiveMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        mrt::TimeoutMessage tMessage = std::get<mrt::TimeoutMessage>(message);
        receiveTimeout(tMessage);
    }
    else if(std::holds_alternative<mrt::RespondTimeMessage>(message)){
        mrt::RespondTimeMessage rMessage = std::get<mrt::RespondTimeMessage>(message);
        receiveMessage(rMessage);
    }
    else{
        throw std::invalid_argument("Main_Capsule unable to handle that message");
    }
}

void Main_Capsule::connect(int clockId){
    _clockId = clockId;
}

void Main_Capsule::start(){
    _state = Running;
    _endTimerId = _timerRunnerPtr->informIn(_id, _timeoutTime);
    _updateTimerId = _timerRunnerPtr->informEvery(_id, _updateTime);
}
        
void Main_Capsule::sendRequestTimeMessage(int toId){
    mrt::VoidMessage outMessage = mrt::RequestTimeMessage;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Main_Capsule::receiveTimeout(const mrt::TimeoutMessage& timeoutMessage){
    if(timeoutMessage.timerId == _endTimerId){
        _state = End;
        std::cout << "Main timeout reached" << std::endl;
        _capsuleRunnerPtr->stop();
    }
    else if(timeoutMessage.timerId == _updateTimerId){
        if(_state == Running){
            _state = WaitForTimeResponse;
            sendRequestTimeMessage(_clockId);
        }
        else{
            std::cout << "Main: unhandled update request" << std::endl;
        }
    }
    else{
        throw std::out_of_range("Main_Capsule does not handle that timer");
    }
}

void Main_Capsule::receiveMessage(const mrt::RespondTimeMessage& inMessage){
    assert(_state == WaitForTimeResponse);
    _state = Running;
    std::cout << "Time: " << inMessage.time << std::endl;
}