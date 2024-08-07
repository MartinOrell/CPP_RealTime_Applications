#include "Ping_Capsule.h"
#include "CapsuleRunner.h"

Ping_Capsule::Ping_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr){
    _count = 0;
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
}

int Ping_Capsule::getId(){
    return _id;
}

void Ping_Capsule::start(){
    std::cout << "Ping: sends ping\n";
    sendMessageToPong(_pongId, _count);
}

void Ping_Capsule::handleMessage(Message message){
    if(std::holds_alternative<TimeoutMessage>(message)){
        handleTimeout(std::get<TimeoutMessage>(message));
    }
    else if(std::holds_alternative<VoidMessage>(message)){
        if(std::get<VoidMessage>(message) == VoidMessage::MessageToPing){
            handleMessageToPing();
        }
        else{
            throw std::invalid_argument("Ping_Capsule unable to handle that voidMessage");
        }
    }
    else{
        throw std::invalid_argument("Ping_Capsule unable to handle that message");
    }
}

void Ping_Capsule::connect(int pongId){
    _pongId = pongId;
}

void Ping_Capsule::sendMessageToPong(int toId, int count){
    MessageToPong outMessage;
    outMessage.count = count;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Ping_Capsule::handleMessageToPing(){
    _timerRunnerPtr->informIn(_id, std::chrono::seconds(1));
}

void Ping_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    std::cout << "Ping: sends ping\n";
    sendMessageToPong(_pongId, ++_count);
}