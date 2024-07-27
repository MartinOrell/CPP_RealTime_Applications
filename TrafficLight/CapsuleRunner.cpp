#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(TimerThread* timerThreadPtr, MessageHandler<Message>* messageHandlerPtr)
:   _trafficLight{0,messageHandlerPtr, timerThreadPtr},
    _messageHandlerPtr{messageHandlerPtr}{
}

void CapsuleRunner::run(){
    
    _trafficLight.start();
    while(true){
        _messageHandlerPtr->waitForMessage();
        Message message = _messageHandlerPtr->receiveMessage();
        if(std::holds_alternative<TimeoutMessage>(message)){
            TimeoutMessage tMessage = std::get<TimeoutMessage>(message);
            if(tMessage.toId == 0){
                _trafficLight.handleTimeout(tMessage);
            }
        }
    }
}