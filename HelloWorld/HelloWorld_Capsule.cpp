#include "HelloWorld_Capsule.h"

HelloWorld_Capsule::HelloWorld_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
}

void HelloWorld_Capsule::start(){
    _state = S1;
    _timerThreadPtr->informIn(_id, std::chrono::seconds(1));
}

void HelloWorld_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    switch(_state){
        case S1:
            {
                _state = S2;
                std::cout << "Hello World!" << std::endl;
                RunInstruction end = RunInstruction::End;
                _messageHandlerPtr->sendMessage(end);
            }
            break;
        default:
            throw std::runtime_error("Timeout not handled in this state");
            break;
    }
}