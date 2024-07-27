#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(MessageHandler<Message>* messageHandlerPtr)
:   _piComputer{messageHandlerPtr},
    _adder{messageHandlerPtr},
    _multiplier{messageHandlerPtr},
    _messageHandlerPtr{messageHandlerPtr}{
}

void CapsuleRunner::run(){
    
    _piComputer.start();
    _adder.start();
    _multiplier.start();
    while(true){
        _messageHandlerPtr->waitForMessage();
        Message message = _messageHandlerPtr->receiveMessage();
        
        if(std::holds_alternative<RunInstruction>(message)){
            RunInstruction instruction = std::get<RunInstruction>(message);
            if(instruction == RunInstruction::End){
                return;
            }
        }
        else if(std::holds_alternative<ComputeRequest>(message)){
            ComputeRequest cMessage = std::get<ComputeRequest>(message);
            _adder.handleMessage(cMessage);
        }
        else if(std::holds_alternative<ComputeResult>(message)){
            ComputeResult cMessage = std::get<ComputeResult>(message);
            _piComputer.handleMessage(cMessage);
        }
        else if(std::holds_alternative<ReturnIncrement>(message)){
            ReturnIncrement rMessage = std::get<ReturnIncrement>(message);
            _adder.handleMessage(rMessage);
        }
        else if(std::holds_alternative<GetIncrement>(message)){
            GetIncrement gMessage = std::get<GetIncrement>(message);
            _multiplier.handleMessage(gMessage);
        }
    }
}