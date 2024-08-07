#include "Client_Capsule.h"
#include "CapsuleRunner.h"

Client_Capsule::Client_Capsule(int id, CapsuleRunner* capsuleRunnerPtr){
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
    Response responseMessage = invokeRequest(_serverId, i);
    std::cout << "Client " << _id <<": Received: " << responseMessage.value << std::endl;
    _capsuleRunnerPtr->stop();
}

Response Client_Capsule::invokeRequest(int toId, int value){
    Request request;
    request.value = value;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = request;
    Message receivedMessage = _capsuleRunnerPtr->invokeMessage(sendMessage);
    assert(std::holds_alternative<Response>(receivedMessage));
    return std::get<Response>(receivedMessage);
}