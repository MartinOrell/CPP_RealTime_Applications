#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(TimerThread* timerThreadPtr, MessageHandler<Message>* messageHandlerPtr)
:   _helloTimer{0,messageHandlerPtr, timerThreadPtr},
    _messageHandlerPtr{messageHandlerPtr}{
}

void CapsuleRunner::run(){
    
    _helloTimer.start();
    while(true){
        _messageHandlerPtr->waitForMessage();
        Message message = _messageHandlerPtr->receiveMessage();
        if(std::holds_alternative<RunInstruction>(message)){
            RunInstruction instruction = std::get<RunInstruction>(message);
            if(instruction == RunInstruction::EndMessage){
                return;
            }
        }
        else if(std::holds_alternative<TimeoutMessage>(message)){
            TimeoutMessage tMessage = std::get<TimeoutMessage>(message);
            if(tMessage.toId == 0){
                _helloTimer.handleTimeout(tMessage);
            }
            else{
                throw std::out_of_range("CapsuleRunner unable to assign timeout to capsule with id: " + std::to_string(tMessage.toId));
            }
        }
        else{
            throw std::invalid_argument("CapsuleRunner received message of unknown type");
        }
    }
}