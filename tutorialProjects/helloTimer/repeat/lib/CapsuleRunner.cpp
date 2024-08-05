#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(int id, MessageHandler* messageHandlerPtr, std::vector<std::unique_ptr<Capsule>>* capsulesPtr)
:   _id{id},
    _messageHandlerPtr{messageHandlerPtr},
    _capsulesPtr{capsulesPtr}{}

void CapsuleRunner::run(){
    
    for(int i = 0; i < _capsulesPtr->size();i++){
        _capsulesPtr->at(i)->start();
    }

    bool running = true;
    while(running){
        _messageHandlerPtr->waitForMessage();
        SendMessage sendMessage = _messageHandlerPtr->receiveMessage();
        running = handleMessage(sendMessage);
    }
}

void CapsuleRunner::stop(){
    VoidMessage outMessage = EndMessage;
    SendMessage sendMessage;
    sendMessage.toId = _id;
    sendMessage.message = outMessage;
    _messageHandlerPtr->sendMessage(sendMessage);
}

Message CapsuleRunner::invokeMessage(SendMessage request){

    for(int i = 0; i < _capsulesPtr->size();i++){
        if(request.toId == _capsulesPtr->at(i)->getId()){
            return _capsulesPtr->at(i)->handleInvokeMessage(request.message);
        }
    }

    throw std::invalid_argument("CapsuleRunner can't invokeMessage to capsule with id: " + std::to_string(request.toId));
}

//handleMessage handles one message
//Returns false if the message is to stop running
//Returns true if successfully called the capsule to handle the message
//throws an error if it fails
bool CapsuleRunner::handleMessage(SendMessage sendMessage){
    if(sendMessage.toId == _id){ //Message to this CapsuleRunner
        Message message = sendMessage.message;
        if(std::holds_alternative<VoidMessage>(message)){
            VoidMessage voidMessage = std::get<VoidMessage>(message);
            if(voidMessage == VoidMessage::EndMessage){
                return false;
            }
            else{
                throw std::invalid_argument("CapsuleRunner received VoidMessage of wrong type");
            }
        }
        else{
            throw std::invalid_argument("CapsuleRunner received message of wrong type");
        }
    }

    //Message is for a capsule, search for the capsule with matching id and send to it
    for(int i = 0; i < _capsulesPtr->size();i++){
        if(sendMessage.toId == _capsulesPtr->at(i)->getId()){
            _capsulesPtr->at(i)->handleMessage(sendMessage.message);
            return true;
        }
    }
    
    throw std::invalid_argument("CapsuleRunner unable to send handleMessage to capsule with id: " + std::to_string(sendMessage.toId));
}