#include "PiComputer_Capsule.h"

PiComputer_Capsule::PiComputer_Capsule(MessageHandler<Message>* messageHandlerPtr){
    _messageHandlerPtr = messageHandlerPtr;
}

void PiComputer_Capsule::start(){
    _state = WaitForComputation;
    int noOfIterations = 100;
    std::cout << "Starting computation of pi using the Madhavas formula with " << noOfIterations << " iterations" << std::endl;
    ComputeRequest outMessage;
    outMessage.noOfIterations = noOfIterations;
    _messageHandlerPtr->sendMessage(outMessage);
}

void PiComputer_Capsule::handleMessage(ComputeResult message){
    _state = Finished;
    std::cout << "Result is : " << std::setprecision(20) << std::fixed << message.result << std::endl;
    RunInstruction end = RunInstruction::End;
    _messageHandlerPtr->sendMessage(end);
}