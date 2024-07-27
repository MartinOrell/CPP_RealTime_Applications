#include "CapsuleController.h"

CapsuleController::CapsuleController(TimerThread* timerThreadPtr, MessageHandler<Message>* messageHandlerPtr)
:   _pinger{0,1,messageHandlerPtr, timerThreadPtr},
    _ponger{1,0,messageHandlerPtr, timerThreadPtr},
    _messageHandlerPtr{messageHandlerPtr}{
}

void CapsuleController::run(){
    
    _pinger.start();
    _ponger.start();
    while(true){
        _messageHandlerPtr->waitForMessage();
        Message message = _messageHandlerPtr->popMessage();
        
        if(std::holds_alternative<TimeoutMessage>(message)){
            TimeoutMessage tMessage = std::get<TimeoutMessage>(message);
            if(tMessage.toId == 0){
                _pinger.handleTimeout(tMessage);
            }
            else{
                _ponger.handleTimeout(tMessage);
            }
        }
        else if(std::holds_alternative<MessageToPing>(message)){
            MessageToPing pMessage = std::get<MessageToPing>(message);
            _pinger.handleMessage(pMessage);
        }
        else if(std::holds_alternative<MessageToPong>(message)){
            MessageToPong pMessage = std::get<MessageToPong>(message);
            _ponger.handleMessage(pMessage);
        }
    }
}