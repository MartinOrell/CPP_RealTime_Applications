#include "Pong_Capsule.h"

Pong_Capsule::Pong_Capsule(int id, MessageHandler<SendMessage>* messageHandlerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
}

int Pong_Capsule::getId(){
    return _id;
}

void Pong_Capsule::start(){}

void Pong_Capsule::handleMessage(Message message){
    if(std::holds_alternative<MessageToPong>(message)){
        handleMessage(std::get<MessageToPong>(message));
    }
    else{
        throw std::invalid_argument("Pong_Capsule unable to handle that message");
    }
}

void Pong_Capsule::connect(int pingId){
    _pingId = pingId;
}

void Pong_Capsule::sendMessageToPing(int toId){
    VoidMessage outMessage = VoidMessage::MessageToPing;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _messageHandlerPtr->sendMessage(sendMessage);
}

void Pong_Capsule::handleMessage(MessageToPong inMessage){
    std::cout << "Pong: sends pong (count = " << inMessage.count << ")" << std::endl;
    sendMessageToPing(_pingId);
}