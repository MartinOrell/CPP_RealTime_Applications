#include "Client_Capsule.h"

#include "CapsuleRunner.h"

#include <cassert>
#include <iostream>

Client_Capsule::Client_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Client_Capsule::getId(){
    return _id;
}

void Client_Capsule::connect(int serverId){
    _serverId = serverId;
}

void Client_Capsule::start(){
    int i = _id*10;
    std::cout << "Client " << _id << ": Sending: " << i << std::endl;
    mrt::Response responseMessage = invokeRequest(_serverId, i);
    std::cout << "Client " << _id <<": Received: " << responseMessage.value << std::endl;
    _capsuleRunnerPtr->stop();
}

mrt::Response Client_Capsule::invokeRequest(int toId, int value){
    mrt::Request request;
    request.value = value;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = request;
    mrt::Message receivedMessage = _capsuleRunnerPtr->invokeMessage(sendMessage);
    assert(std::holds_alternative<mrt::Response>(receivedMessage));
    return std::get<mrt::Response>(receivedMessage);
}