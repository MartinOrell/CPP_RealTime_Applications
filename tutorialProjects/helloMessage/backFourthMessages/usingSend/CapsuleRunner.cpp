#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(MessageHandler<Message>* messageHandlerPtr)
:   _client{CLIENTID,messageHandlerPtr},
    _server{SERVERID,messageHandlerPtr},
    _messageHandlerPtr{messageHandlerPtr}{

    _client.connect(SERVERID);
    _server.connect(CLIENTID);
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
        else if(std::holds_alternative<Request>(message)){
            Request rMessage = std::get<Request>(message);
            _server.handleMessage(rMessage);
        }
        else if(std::holds_alternative<Response>(message)){
            Response rMessage = std::get<Response>(message);
            _client.handleMessage(rMessage);
        }
        else{
            throw std::invalid_argument("CapsuleRunner received message of unknown type");
        }
    }
}