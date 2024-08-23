#include "Client_Capsule.h"

#include "CapsuleRunner.h"

#include <stdexcept>
#include <iostream>

Client_Capsule::Client_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Client_Capsule::getId(){
    return _id;
}

void Client_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::Response>(message)){
        handleMessage(std::get<mrt::Response>(message));
    }
    else{
        throw std::invalid_argument("Client_Capsule unable to handle that message");
    }
}

void Client_Capsule::connect(int serverId){
    _serverId = serverId;
}

void Client_Capsule::sendMessage(int toId, int value){
    mrt::Request outMessage;
    outMessage.value = value;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Client_Capsule::start(){
    int i = 5;
    std::cout << "Client: Sending: " << i << std::endl;
    sendMessage(_serverId, i);
    _state = WaitForResponse;
}

void Client_Capsule::handleMessage(const mrt::Response& message){
    if(_state == WaitForResponse){
        std::cout << "Client: Received: " << message.value << std::endl;
        _capsuleRunnerPtr->stop();
        _state = End;
    }
    else{
        throw std::invalid_argument("Client can not handle a Response message in state " + std::to_string(_state));
    }
}