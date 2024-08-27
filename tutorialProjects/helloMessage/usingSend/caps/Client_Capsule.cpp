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

void Client_Capsule::receiveMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::Response>(message)){
        receiveMessage(std::get<mrt::Response>(message));
        return;
    }
    
    std::string errorMsg =
        "Client_Capsule unable receive Message[" +
        std::to_string(message.index()) +
        "]";
    throw std::invalid_argument(errorMsg);
}

void Client_Capsule::start(){
    int i = 5;
    std::cout << "Client: Sending: " << i << std::endl;
    sendMessage(_serverId, i);
    _state = State::WaitForResponse;
}

void Client_Capsule::receiveMessage(const mrt::Response& message){
    if(_state != State::WaitForResponse){
        std::string errorMsg =
            "Client_Capsule received a Response message, but can't receive it in state[" +
            std::to_string(_state) +
            "]";
        throw std::invalid_argument(errorMsg);
    }

    std::cout << "Client: Received: " << message.value << std::endl;
    _capsuleRunnerPtr->stop();
    _state = State::End;
}