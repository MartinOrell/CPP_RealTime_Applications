#include "HelloWorld_Capsule.h"
#include "CapsuleRunner.h"

HelloWorld_Capsule::HelloWorld_Capsule(int id, MessageHandler<SendMessage>* messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int HelloWorld_Capsule::getId(){
    return _id;
}

void HelloWorld_Capsule::start(){
    _state = S1;
    _timerThreadPtr->informIn(_id, std::chrono::seconds(1));
}

void HelloWorld_Capsule::handleMessage(Message message){
    if(std::holds_alternative<TimeoutMessage>(message)){
        handleTimeout(std::get<TimeoutMessage>(message));
    }
    else{
        throw std::invalid_argument("HelloWorld_Capsule unable to handle that message");
    }
}

void HelloWorld_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    switch(_state){
        case S1:
            {
                _state = S2;
                std::cout << "Hello World!" << std::endl;
                _capsuleRunnerPtr->stop();
            }
            break;
        default:
            throw std::runtime_error("Timeout not handled in this state");
            break;
    }
}