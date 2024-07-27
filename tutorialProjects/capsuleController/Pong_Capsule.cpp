#include "Pong_Capsule.h"

Pong_Capsule::Pong_Capsule(int id, int connectionToId, MessageHandler<Message>* messageHandlerPtr){
    _id = id;
    _connectionToId = connectionToId;
    _messageHandlerPtr = messageHandlerPtr;
}

void Pong_Capsule::start(){}

void Pong_Capsule::handleMessage(MessageToPong inMessage){
    std::cout << "Pong: sends pong (count = " << inMessage.count << ")" << std::endl;
    MessageToPing outMessage;
    outMessage.toId = _connectionToId;
    _messageHandlerPtr->sendMessage(outMessage);
}

void Pong_Capsule::handleTimeout(TimeoutMessage timeoutMessage){}