#include "Server_Capsule.h"

Server_Capsule::Server_Capsule(int id, MessageHandler<Message>* messageHandlerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
}

void Server_Capsule::connect(int clientId){
    _clientId = clientId;
}

void Server_Capsule::start(){}

void Server_Capsule::handleMessage(Request inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    Response outMessage;
    outMessage.toId = _clientId;
    outMessage.value = i;
    _messageHandlerPtr->sendMessage(outMessage);
}