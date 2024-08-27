#include "Server_Capsule.h"

#include <stdexcept>
#include <iostream>

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

mrt::Message Server_Capsule::receiveInvokeMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::Request>(message)){
        return receiveInvokeMessage(std::get<mrt::Request>(message));
    }
    else{
        std::string errorMsg =
            "Server_Capsule[" +
            std::to_string(_id) +
            "] unable to receive invoke with Message[" +
            std::to_string(message.index()) +
            "]";
        throw std::invalid_argument(errorMsg);
    }
}

mrt::Message Server_Capsule::receiveInvokeMessage(const mrt::Request& inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    mrt::Response outMessage;
    outMessage.value = i;
    return outMessage;
}