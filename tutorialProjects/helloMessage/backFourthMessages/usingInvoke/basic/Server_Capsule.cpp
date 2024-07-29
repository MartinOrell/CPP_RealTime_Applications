#include "Server_Capsule.h"

Server_Capsule::Server_Capsule(int id){
    _id = id;
}

int Server_Capsule::getId(){
    return _id;
}

void Server_Capsule::connect(int clientId){
    _clientId = clientId;
}

void Server_Capsule::start(){}

Message Server_Capsule::handleInvokeMessage(Request inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    Response outMessage;
    outMessage.toId = _clientId;
    outMessage.value = i;
    return outMessage;
}