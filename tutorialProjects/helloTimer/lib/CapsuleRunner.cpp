#include "CapsuleRunner.h"
#include "MessageManager.h"

CapsuleRunner::CapsuleRunner(int id, MessageManager* messageManagerPtr)
:   _id{id},
    _messageManagerPtr{messageManagerPtr},
    _nextTimerId{0}{
        _messageManagerPtr->addCapsuleRunnerPtr(this);
    }

void CapsuleRunner::addCapsule(std::unique_ptr<Capsule> capsule){
    _capsules.push_back(std::move(capsule));
}

bool CapsuleRunner::isResponsible(int id){
    if(id == _id){
        return true;
    }
    for(int i = 0; i < _capsules.size();i++){
        if(id == _capsules.at(i)->getId()){
            return true;
        }
    }
    return false;
}

void CapsuleRunner::run(){
    
    for(int i = 0; i < _capsules.size();i++){
        _capsules.at(i)->start();
    }

    bool running = true;
    while(running){

        if(_timers.size() == 0){
            _messageHandler.waitForMessage();
            SendMessage sendMessage = _messageHandler.receiveMessage();
            running = handleMessage(sendMessage);
            continue;
        }

        auto nextTimeout = std::min_element(_timers.begin(), _timers.end());
        auto now = std::chrono::steady_clock::now();
        if(now >= nextTimeout->timeoutTime){
            handleTimeout(now, nextTimeout);
            continue;
        }

        if(_messageHandler.waitForMessageUntil(nextTimeout->timeoutTime)){
            //message arrived
            SendMessage sendMessage = _messageHandler.receiveMessage();
            running = handleMessage(sendMessage);
            continue;
        }

        //Timeout reached
        handleTimeout(now,nextTimeout);
    }
}

void CapsuleRunner::stop(){
    VoidMessage outMessage = EndMessage;
    SendMessage sendMessage;
    sendMessage.toId = _id;
    sendMessage.message = outMessage;
    _messageHandler.sendMessage(sendMessage);
}

void CapsuleRunner::sendMessage(SendMessage message){
    if(isResponsible(message.toId)){
        _messageHandler.sendMessage(message);
    }
    else{
        _messageManagerPtr->sendMessage(message);
    }
}

void CapsuleRunner::mergeOrSendMessage(SendMessage message){
    if(isResponsible(message.toId)){
        _messageHandler.mergeOrSendMessage(message);
    }
    else{
        _messageManagerPtr->mergeOrSendMessage(message);
    }
}

Message CapsuleRunner::invokeMessage(SendMessage request){

    for(int i = 0; i < _capsules.size();i++){
        if(request.toId == _capsules.at(i)->getId()){
            return _capsules.at(i)->handleInvokeMessage(request.message);
        }
    }

    throw std::invalid_argument("CapsuleRunner[" + std::to_string(_id) + "] can't invokeMessage to capsule with id: " + std::to_string(request.toId));
}

int CapsuleRunner::informIn(int toId, std::chrono::steady_clock::duration duration){
    Timer timer;
    timer.id = _nextTimerId++;
    timer.toId = toId;
    timer.timeoutTime = std::chrono::steady_clock::now() + duration;
    timer.isRepeating = false;
    SendMessage message;
    message.toId = _id;
    message.message = timer;
    _messageHandler.sendMessage(message);
    return timer.id;
}

int CapsuleRunner::informEvery(int toId, std::chrono::steady_clock::duration interval){
    assert(interval > std::chrono::nanoseconds(0));
    Timer timer;
    timer.id = _nextTimerId++;
    timer.toId = toId;
    timer.timeoutTime = std::chrono::steady_clock::now() + interval;
    timer.isRepeating = true;
    timer.interval = interval;
    SendMessage message;
    message.toId = _id;
    message.message = timer;
    _messageHandler.sendMessage(message);
    return timer.id;
}

void CapsuleRunner::cancelTimer(int id){
    CancelTimer cancelTimer;
    cancelTimer.id = id;
    SendMessage message;
    message.toId = _id;
    message.message = cancelTimer;
    _messageHandler.sendMessage(message);
}

//handleMessage handles one message
//Returns false if the message is to stop running
//Returns true if successfully called the capsule to handle the message
//throws an error if it fails
bool CapsuleRunner::handleMessage(SendMessage sendMessage){
    if(sendMessage.toId == _id){
        return handleMessageToMe(sendMessage.message);
    }

    //Message is for a capsule, search for the capsule with matching id and send to it
    for(int i = 0; i < _capsules.size();i++){
        if(sendMessage.toId == _capsules.at(i)->getId()){
            _capsules.at(i)->handleMessage(sendMessage.message);
            return true;
        }
    }
    
    throw std::invalid_argument("CapsuleRunner[" + std::to_string(_id) + "] unable to send handleMessage to capsule with id: " + std::to_string(sendMessage.toId));
}

bool CapsuleRunner::handleMessageToMe(Message message){
    if(std::holds_alternative<VoidMessage>(message)){
        VoidMessage voidMessage = std::get<VoidMessage>(message);
        if(voidMessage == VoidMessage::EndMessage){
            return false;
        }
        else{
            throw std::invalid_argument("CapsuleRunner[" + std::to_string(_id) + "] can't handle Voidmessage: " + std::to_string(voidMessage));
        }
    }
    else if(std::holds_alternative<Timer>(message)){
        Timer timer = std::get<Timer>(message);
        _timers.push_back(timer);
        return true;
    }
    else if (std::holds_alternative<CancelTimer>(message)){
        int m_id = std::get<CancelTimer>(message).id;
        _timers.erase(std::remove_if(_timers.begin(), _timers.end(),[m_id](Timer t) { return (t.id == m_id); }), _timers.end());
        return true;
    }
    else{
        throw std::invalid_argument("CapsuleRunner[" + std::to_string(_id) + "] can't handle message to him with type index: " + std::to_string(message.index()));
    }
}

void CapsuleRunner::handleTimeout(std::chrono::steady_clock::time_point now, std::vector<Timer>::iterator nextTimeout){

    int timeouts = 1;
    if(nextTimeout->isRepeating){
        timeouts = 1 + (now-nextTimeout->timeoutTime)/nextTimeout->interval;
    }
    mergeOrSendTimeoutMessage(nextTimeout->toId, nextTimeout->id, timeouts);
    if(nextTimeout->isRepeating){
        nextTimeout->timeoutTime+=nextTimeout->interval*timeouts;
    }
    else{
        _timers.erase(nextTimeout);
    }
}

void CapsuleRunner::mergeOrSendTimeoutMessage(int toId, int timerId, int timeouts){
    TimeoutMessage message;
    message.timerId = timerId;
    message.timeouts = timeouts;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = message;
    if(isResponsible(toId)){
        _messageHandler.mergeOrSendMessage(sendMessage);
    }
    else{
        _messageManagerPtr->mergeOrSendMessage(sendMessage);
    }
}