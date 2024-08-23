#include "Pong_Capsule.h"

#include "CapsuleRunner.h"

#include <stdexcept>
#include <iostream>

Pong_Capsule::Pong_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
}

int Pong_Capsule::getId(){
    return _id;
}

void Pong_Capsule::start(){}

void Pong_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::MessageToPong>(message)){
        handleMessage(std::get<mrt::MessageToPong>(message));
    }
    else{
        throw std::invalid_argument("Pong_Capsule unable to handle that message");
    }
}

void Pong_Capsule::connect(int pingId){
    _pingId = pingId;
}

void Pong_Capsule::sendMessageToPing(int toId){
    mrt::VoidMessage outMessage = mrt::VoidMessage::MessageToPing;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Pong_Capsule::handleMessage(const mrt::MessageToPong& inMessage){
    std::cout << "Pong: sends pong (count = " << inMessage.count << ")" << std::endl;
    sendMessageToPing(_pingId);
}