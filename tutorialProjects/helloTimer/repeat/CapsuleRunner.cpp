#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(TimerThread* timerThreadPtr, MessageHandler<SendMessage>* messageHandlerPtr)
:   _helloTimer{0,messageHandlerPtr, timerThreadPtr},
    _messageHandlerPtr{messageHandlerPtr}{
}

void CapsuleRunner::run(){
    
    _helloTimer.start();
    while(true){
        _messageHandlerPtr->waitForMessage();
        SendMessage sendMessage = _messageHandlerPtr->receiveMessage();
        Message message = sendMessage.message;
        if(std::holds_alternative<RunInstruction>(message)){
            RunInstruction instruction = std::get<RunInstruction>(message);
            if(instruction == RunInstruction::EndMessage){
                return;
            }
        }
        else if(std::holds_alternative<TimeoutMessage>(message)){
            TimeoutMessage tMessage = std::get<TimeoutMessage>(message);
            _helloTimer.handleTimeout(tMessage);
        }
        else{
            throw std::invalid_argument("CapsuleRunner received message of unknown type");
        }
    }
}