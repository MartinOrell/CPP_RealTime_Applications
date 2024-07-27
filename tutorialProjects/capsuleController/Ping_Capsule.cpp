#include "Ping_Capsule.h"

Ping_Capsule::Ping_Capsule(){}

Ping_Capsule::Ping_Capsule(int id, int connectionId, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr){
    _count = 0;
    _id = id;
    _connectionId = connectionId;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
}

void Ping_Capsule::start(){
    std::cout << "Ping: sends ping\n";
    MessageToPong message;
    message.toId = _connectionId;
    message.count = _count;
    _messageHandlerPtr->addMessage(message);
}

void Ping_Capsule::handleMessage(MessageToPing message){
    _timerThreadPtr->informIn(_id, std::chrono::seconds(1));
}

void Ping_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    std::cout << "Ping: sends ping\n";
    MessageToPong message;
    message.toId = _connectionId;
    message.count = ++_count;
    _messageHandlerPtr->addMessage(message);
}