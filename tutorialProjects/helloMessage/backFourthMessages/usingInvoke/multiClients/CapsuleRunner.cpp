#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(MessageHandler<Message>* messageHandlerPtr)
:   _nextCapsuleId{0},
    _clients{{_nextCapsuleId++,messageHandlerPtr,this},{_nextCapsuleId++,messageHandlerPtr,this},{_nextCapsuleId++,messageHandlerPtr,this}},
    _server{_nextCapsuleId++},
    _messageHandlerPtr{messageHandlerPtr}{

    for(int i = 0; i<3; i++){
        _clients[i].connect(_server.getId());
        _server.connect(i, _clients[i].getId());
    }
}

void CapsuleRunner::run(){
    
    for(int i = 0; i<3; i++){
        _clients[i].start();
    }
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