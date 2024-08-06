#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(int id, MessageHandler* messageHandlerPtr, std::vector<std::unique_ptr<Capsule>>* capsulesPtr)
:   _id{id},
    _messageHandlerPtr{messageHandlerPtr},
    _capsulesPtr{capsulesPtr},
    _nextTimerId{0}{}

void CapsuleRunner::run(){
    
    for(int i = 0; i < _capsulesPtr->size();i++){
        _capsulesPtr->at(i)->start();
    }

    bool running = true;
    while(running){

        if(_timers.size() == 0){
            _messageHandlerPtr->waitForMessage();
            SendMessage sendMessage = _messageHandlerPtr->receiveMessage();
            running = handleMessage(sendMessage);
            continue;
        }

        auto nextTimeout = std::min_element(_timers.begin(), _timers.end());
        auto now = std::chrono::steady_clock::now();
        if(now >= nextTimeout->timeoutTime){
            handleTimeout(now, nextTimeout);
            continue;
        }

        if(_messageHandlerPtr->waitForMessageUntil(nextTimeout->timeoutTime)){
            //message received
            SendMessage sendMessage = _messageHandlerPtr->receiveMessage();
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

int CapsuleRunner::informIn(int toId, std::chrono::steady_clock::duration duration){
    Timer timer;
    timer.id = _nextTimerId++;
    timer.toId = toId;
    timer.timeoutTime = std::chrono::steady_clock::now() + duration;
    timer.isRepeating = false;
    SendMessage message;
    message.toId = _id;
    message.message = timer;
    _messageHandlerPtr->sendMessage(message);
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
    _messageHandlerPtr->sendMessage(message);
    return timer.id;
}

void CapsuleRunner::cancelTimer(int id){
    CancelTimer cancelTimer;
    cancelTimer.id = id;
    SendMessage message;
    message.toId = _id;
    message.message = cancelTimer;
    _messageHandlerPtr->sendMessage(message);
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
    _messageHandlerPtr->mergeOrSendMessage(sendMessage);
}