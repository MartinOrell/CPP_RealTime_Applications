#include "Client_Capsule.h"
#include "CapsuleRunner.h"

Client_Capsule::Client_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
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
    Request requestMessage;
    requestMessage.toId = _serverId;
    requestMessage.value = i;
    Message genericResponseMessage = _capsuleRunnerPtr->invokeMessage(requestMessage);
    assert(std::holds_alternative<Response>(genericResponseMessage));
    Response responseMessage = std::get<Response>(genericResponseMessage);
    std::cout << "Client " << _id <<": Received: " << responseMessage.value << std::endl;
    RunInstruction end = RunInstruction::EndMessage;
    _messageHandlerPtr->sendMessage(end);
}