#include "Main_Capsule.h"

Main_Capsule::Main_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr, std::chrono::steady_clock::duration timeoutTime, int fps){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
    _timeoutTime = timeoutTime;
    _updateTime = std::chrono::milliseconds(1000/fps);
    if(_updateTime <= std::chrono::milliseconds(0)){
        throw std::range_error("updateTime is too low, try a lower fps");
    }
}

int Main_Capsule::getId(){
    return _id;
}

void Main_Capsule::connect(int clockId){
    _clockId = clockId;
}

void Main_Capsule::start(){
    _state = Running;
    _endTimerId = _timerThreadPtr->informIn(_id, _timeoutTime);
    _updateTimerId = _timerThreadPtr->informEvery(_id, _updateTime);
}

void Main_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    if(timeoutMessage.timerId == _endTimerId){
        _state = End;
        std::cout << "Main timeout reached" << std::endl;
        NoContentMessage outMessage = EndMessage;
        _messageHandlerPtr->sendMessage(outMessage);
    }
    else if(timeoutMessage.timerId == _updateTimerId){
        if(_state == Running){
            _state = WaitForTimeResponse;
            NoContentMessage outMessage = RequestTimeMessage;
            _messageHandlerPtr->sendMessage(outMessage);
        }
        else{
            std::cout << "Main: unhandled update request" << std::endl;
        }
    }
    else{
        throw std::out_of_range("Main_Capsule does not handle that timer");
    }
}

void Main_Capsule::handleMessage(RespondTimeMessage inMessage){
    assert(_state == WaitForTimeResponse);
    _state = Running;
    std::cout << "Time: " << inMessage.time << std::endl;
}