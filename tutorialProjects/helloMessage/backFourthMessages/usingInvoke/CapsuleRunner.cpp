#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(MessageHandler<Message>* messageHandlerPtr)
:   _nextCapsuleId{0},
    _client{_nextCapsuleId++,messageHandlerPtr,this},
    _server{_nextCapsuleId++},
    _messageHandlerPtr{messageHandlerPtr}{

    _client.connect(_server.getId());
    _server.connect(_client.getId());
}

void CapsuleRunner::run(){
    
    _client.start();
    _server.start();
    while(true){
        _messageHandlerPtr->waitForMessage();
        Message message = _messageHandlerPtr->receiveMessage();
        
        if(std::holds_alternative<RunInstruction>(message)){
            RunInstruction instruction = std::get<RunInstruction>(message);
            if(instruction == RunInstruction::EndMessage){
                return;
            }
        }
        else{
            throw std::invalid_argument("CapsuleRunner received message of wrong type");
        }
    }
}

Message CapsuleRunner::invokeMessage(Message request){
    if(std::holds_alternative<Request>(request)){
        Request rMessage = std::get<Request>(request);
        return _server.handleInvokeMessage(rMessage);
    }
    else{
        throw std::invalid_argument("CapsuleRunner received invokeMessage of wrong type");
    }
}