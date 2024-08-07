#include "MessageManager.h"

MessageManager::MessageManager(){}

void MessageManager::addCapsuleRunnerPtr(CapsuleRunner* capsuleRunner){
    _capsuleRunnerPtrs.push_back(capsuleRunner);
}

void MessageManager::sendMessage(SendMessage sendMessage){
    for(auto it = _capsuleRunnerPtrs.begin(); it < _capsuleRunnerPtrs.end(); it++){
        if((*it)->isResponsible(sendMessage.toId)){
            (*it)->sendMessage(sendMessage);
            return;
        }
    }
    throw std::invalid_argument("MessageManager unable to send message to id: " + std::to_string(sendMessage.toId));
}

void MessageManager::mergeOrSendMessage(SendMessage sendMessage){
    for(auto it = _capsuleRunnerPtrs.begin(); it < _capsuleRunnerPtrs.end(); it++){
        if((*it)->isResponsible(sendMessage.toId)){
            (*it)->mergeOrSendMessage(sendMessage);
            return;
        }
    }
    throw std::invalid_argument("MessageManager unable to send message to id: " + std::to_string(sendMessage.toId));

}