#include "Multiplier_Capsule.h"

Multiplier_Capsule::Multiplier_Capsule(int id, MessageHandler<SendMessage>* messageHandlerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
}

int Multiplier_Capsule::getId(){
    return _id;
}

void Multiplier_Capsule::start(){}

void Multiplier_Capsule::handleMessage(Message message){
    if(std::holds_alternative<GetIncrement>(message)){
        handleMessage(std::get<GetIncrement>(message));
    }
    else{
        throw std::invalid_argument("Multiplier_Capsule unable to handle that message");
    }
}

void Multiplier_Capsule::connectAdder(int adderId){
    _adderId = adderId;
}

void Multiplier_Capsule::sendReturnIncrementMessage(int toId, double inc){
    ReturnIncrement outMessage;
    outMessage.inc = inc;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _messageHandlerPtr->sendMessage(sendMessage);
}

void Multiplier_Capsule::handleMessage(GetIncrement inMessage){
    int k = inMessage.remainingIterations;
    double inc = std::pow(-3, -k) / (2 * k + 1);
    sendReturnIncrementMessage(_adderId, inc);
}