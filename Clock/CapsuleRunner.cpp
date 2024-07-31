#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(MessageHandler<SendMessage>* messageHandlerPtr, std::vector<std::unique_ptr<Capsule>>* capsulesPtr)
:   _messageHandlerPtr{messageHandlerPtr},
    _capsulesPtr{capsulesPtr}{}

void CapsuleRunner::run(){
    
    for(int i = 0; i < _capsulesPtr->size();i++){
        _capsulesPtr->at(i)->start();
    }

    while(true){
        _messageHandlerPtr->waitForMessage();
        SendMessage sendMessage = _messageHandlerPtr->receiveMessage();
        if(sendMessage.toId == -1){
            Message message = sendMessage.message;
            if(std::holds_alternative<NoContentMessage>(message)){
                NoContentMessage emptyMessage = std::get<NoContentMessage>(message);
                if(emptyMessage == NoContentMessage::EndMessage){
                    return;
                }
                else{
                    throw std::invalid_argument("CapsuleRunner received emptyMessage of wrong type");
                }
            }
            else{
                throw std::invalid_argument("CapsuleRunner received message of wrong type");
            }
        }
        else{
            bool isMessageHandled = false;
            for(int i = 0; i < _capsulesPtr->size();i++){
                if(sendMessage.toId == _capsulesPtr->at(i)->getId()){
                    _capsulesPtr->at(i)->handleMessage(sendMessage.message);
                    isMessageHandled = true;
                    break;
                }
            }
            if(!isMessageHandled){
                throw std::invalid_argument("CapsuleRunner unable to send handleMessage to capsule with id: " + std::to_string(sendMessage.toId));
            }
        }
    }
}

Message CapsuleRunner::invokeMessage(SendMessage request){

    for(int i = 0; i < _capsulesPtr->size();i++){
        if(request.toId == _capsulesPtr->at(i)->getId()){
            return _capsulesPtr->at(i)->handleInvokeMessage(request.message);
        }
    }

    throw std::invalid_argument("CapsuleRunner can't invokeMessage to capsule with id: " + std::to_string(request.toId));
}