#include "Server_Capsule.h"

#include "CapsuleRunner.h"

#include <stdexcept>
#include <iostream>

Server_Capsule::Server_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Server_Capsule::getId(){
    return _id;
}

void Server_Capsule::connect(int clientId){
    _clientId = clientId;
}

void Server_Capsule::sendMessage(int toId, int value){
    mrt::Response outMessage;
    outMessage.value = value;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Server_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::Request>(message)){
        receiveMessage(std::get<mrt::Request>(message));
        return;
    }

    std::string errorMsg =
        "Server_Capsule unable receive Message[" +
        std::to_string(message.index()) +
        "]";
    throw std::invalid_argument(errorMsg);
}

void Server_Capsule::start(){}

void Server_Capsule::receiveMessage(const mrt::Request& inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    sendMessage(_clientId, i);
}