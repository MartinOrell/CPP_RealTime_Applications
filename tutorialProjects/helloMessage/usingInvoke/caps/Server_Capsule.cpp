#include "Server_Capsule.h"

Server_Capsule::Server_Capsule(int id, int numClients){
    _id = id;
    _clientIds.resize(numClients, -1);
}

int Server_Capsule::getId(){
    return _id;
}

void Server_Capsule::connect(int index, int clientId){
    _clientIds.at(index) = clientId;
}

void Server_Capsule::start(){}

mrt::Message Server_Capsule::handleInvokeMessage(mrt::Message message){
    if(std::holds_alternative<mrt::Request>(message)){
        return handleInvokeMessage(std::get<mrt::Request>(message));
    }
    else{
        throw std::invalid_argument("Server_Capsule[" + std::to_string(_id) + "] unable to invokeMessage with message type index " + std::to_string(message.index()));
    }
}

mrt::Message Server_Capsule::handleInvokeMessage(mrt::Request inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    mrt::Response outMessage;
    outMessage.value = i;
    return outMessage;
}