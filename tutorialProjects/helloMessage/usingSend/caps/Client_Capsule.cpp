#include "Client_Capsule.h"
#include "CapsuleRunner.h"

Client_Capsule::Client_Capsule(int id, CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Client_Capsule::getId(){
    return _id;
}

void Client_Capsule::handleMessage(Message message){
    if(std::holds_alternative<Response>(message)){
        handleMessage(std::get<Response>(message));
    }
    else{
        throw std::invalid_argument("Client_Capsule unable to handle that message");
    }
}

void Client_Capsule::connect(int serverId){
    _serverId = serverId;
}

void Client_Capsule::sendMessage(int toId, int value){
    Request outMessage;
    outMessage.value = value;
    SendMessage sendMessage;
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

void Client_Capsule::handleMessage(Response message){
    if(_state == WaitForResponse){
        std::cout << "Client: Received: " << message.value << std::endl;
        _capsuleRunnerPtr->stop();
        _state = End;
    }
    else{
        throw std::invalid_argument("Client can not handle a Response message in state " + std::to_string(_state));
    }
}