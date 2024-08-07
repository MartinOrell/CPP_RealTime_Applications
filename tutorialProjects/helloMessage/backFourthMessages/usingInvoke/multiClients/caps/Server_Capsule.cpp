#include "Server_Capsule.h"

Server_Capsule::Server_Capsule(int id){
    _id = id;
}

int Server_Capsule::getId(){
    return _id;
}

void Server_Capsule::connect(int index, int clientId){
    _clientIds[index] = clientId;
}

void Server_Capsule::start(){}

Message Server_Capsule::handleInvokeMessage(Message message){
    if(std::holds_alternative<Request>(message)){
        return handleInvokeMessage(std::get<Request>(message));
    }
    else{
        throw std::invalid_argument("Server_Capsule[" + std::to_string(_id) + "] unable to invokeMessage with message type index " + std::to_string(message.index()));
    }
}

Message Server_Capsule::handleInvokeMessage(Request inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    Response outMessage;
    outMessage.value = i;
    return outMessage;
}