#include "Server_Capsule.h"
#include "CapsuleRunner.h"

Server_Capsule::Server_Capsule(int id, CapsuleRunner* capsuleRunnerPtr){
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
    Response outMessage;
    outMessage.value = value;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Server_Capsule::handleMessage(Message message){
    if(std::holds_alternative<Request>(message)){
        handleMessage(std::get<Request>(message));
    }
    else{
        throw std::invalid_argument("Client_Capsule unable to handle that message");
    }
}

void Server_Capsule::start(){}

void Server_Capsule::handleMessage(Request inMessage){
    int i = inMessage.value;
    std::cout << "Server: Received: " << i << std::endl;
    i++;
    std::cout << "Server: Sending: " << i << std::endl;
    sendMessage(_clientId, i);
}