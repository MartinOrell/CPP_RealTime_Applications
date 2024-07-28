#include "HelloTimer_Capsule.h"

HelloTimer_Capsule::HelloTimer_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
}

void HelloTimer_Capsule::start(){
    _state = Running;
    std::cout << "Hello World!" << std::endl;
    _endTimerId = _timerThreadPtr->informIn(_id, std::chrono::seconds(2));
}

void HelloTimer_Capsule::handleTimeout(TimeoutMessage timeoutMessage){

    if(timeoutMessage.timerId == _endTimerId && _state == Running){
        _state = End;
        std::cout << "Goodbye World!" << std::endl;
        RunInstruction end = RunInstruction::EndMessage;
        _messageHandlerPtr->sendMessage(end);
    }
    else{
        throw std::out_of_range("HelloTimer does not support timeout with id " + std::to_string(timeoutMessage.timerId) + " in state " + std::to_string(_state));
    }
}