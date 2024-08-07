#include "Client_Capsule.h"

Client_Capsule::Client_Capsule(int id, MessageHandler<Message>* messageHandlerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
}

int Client_Capsule::getId(){
    return _id;
}

void Client_Capsule::connect(int serverId){
    _serverId = serverId;
}

void Client_Capsule::start(){
    int i = 5;
    std::cout << "Client: Sending: " << i << std::endl;
    Request message;
    message.toId = _serverId;
    message.value = i;
    _messageHandlerPtr->sendMessage(message);
    _state = WaitForResponse;
}

void Client_Capsule::handleMessage(Response message){
    if(_state == WaitForResponse){
        std::cout << "Client: Received: " << message.value << std::endl;
        RunInstruction end = RunInstruction::EndMessage;
        _messageHandlerPtr->sendMessage(end);
        _state = End;
    }
    else{
        throw std::invalid_argument("Client can not handle a Response message in state " + std::to_string(_state));
    }
}