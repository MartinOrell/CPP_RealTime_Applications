#include "Adder_Capsule.h"

Adder_Capsule::Adder_Capsule(MessageHandler<Message>* messageHandlerPtr){
    _messageHandlerPtr = messageHandlerPtr;
}

void Adder_Capsule::start(){
    _state = Idle;
}

void Adder_Capsule::handleMessage(ComputeRequest inMessage){
    _state = Computing;
    _remainingIterations = inMessage.noOfIterations-1;
    GetIncrement outMessage;
    outMessage.remainingIterations = _remainingIterations;
    _messageHandlerPtr->sendMessage(outMessage);
}

void Adder_Capsule::handleMessage(ReturnIncrement inMessage){
    double inc = inMessage.inc;
    printDouble(inc, _remainingIterations);
    _result+=inc;
    if(_remainingIterations == 0){
        _state = Idle;
        _result = sqrt(12) * _result;
        ComputeResult outMessage;
        outMessage.result = _result;
        _messageHandlerPtr->sendMessage(outMessage);
    }
    else{
        _state = Computing;
        _remainingIterations--;
        GetIncrement outMessage;
        outMessage.remainingIterations = _remainingIterations;
        _messageHandlerPtr->sendMessage(outMessage);
    }
}

void Adder_Capsule::printDouble(double p1, int inc) {
    std::cout << "double " << p1 << " int " << inc << std::endl;
}