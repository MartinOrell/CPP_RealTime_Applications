#include "Multiplier_Capsule.h"

Multiplier_Capsule::Multiplier_Capsule(MessageHandler<Message>* messageHandlerPtr){
    _messageHandlerPtr = messageHandlerPtr;
}

void Multiplier_Capsule::start(){}

void Multiplier_Capsule::handleMessage(GetIncrement inMessage){
    int k = inMessage.remainingIterations;
    double inc = std::pow(-3, -k) / (2 * k + 1);
    ReturnIncrement outMessage;
    outMessage.inc = inc;
    _messageHandlerPtr->sendMessage(outMessage);
}