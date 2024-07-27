#include "Pong_Capsule.h"

Pong_Capsule::Pong_Capsule(){}

Pong_Capsule::Pong_Capsule(int id, int connectionId, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr){
    _id = id;
    _connectionId = connectionId;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
}

void Pong_Capsule::start(){}

void Pong_Capsule::handleMessage(MessageToPong inMessage){
    std::cout << "Pong: sends pong (count = " << inMessage.count << ")" << std::endl;
    MessageToPing outMessage;
    outMessage.toId = _connectionId;
    _messageHandlerPtr->addMessage(outMessage);
}

void Pong_Capsule::handleTimeout(TimeoutMessage timeoutMessage){}