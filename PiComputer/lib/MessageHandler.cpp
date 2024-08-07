#include "MessageHandler.h"

MessageHandler::MessageHandler(){
    _waitForMessageMutex.lock();
}

void MessageHandler::sendMessage(SendMessage message){
    _mutex.lock();
    _messageStack.push_back(message);
    _mutex.unlock();
    _waitForMessageMutex.unlock();
}

//Requires equal operator and merge function for SendMessage
void MessageHandler::mergeOrSendMessage(SendMessage message){
    _mutex.lock();
    auto it = std::find(_messageStack.begin(), _messageStack.end(), message);
    if(it==_messageStack.end()){
        _messageStack.push_back(message);
        _mutex.unlock();
        _waitForMessageMutex.unlock();
        return;
    }
    it->merge(message);
    _mutex.unlock();
}

//receiveMessage returns the top message on the stack
//Caller should check with hasMessage(), WaitForMessage() or WaitForMessageUntil()
//before calling this function
SendMessage MessageHandler::receiveMessage(){
    assert(_messageStack.size() > 0);
    _mutex.lock();
    SendMessage message = _messageStack.back();
    _messageStack.pop_back();
    if(_messageStack.size() > 0)
    {
        _waitForMessageMutex.unlock();
    }
    _mutex.unlock();
    return message;
}

//hasMessage returns true if a message is on the stack
//also returns true if stop is called
//Does not block
//Requires caller to followup with receiveMessage if a message is found
bool MessageHandler::hasMessage(){
    return _waitForMessageMutex.try_lock();
}

//waitForMessage waits until a message is on the stack
//also stops waiting if stop is called
//Blocks the thread while waiting
//Requires caller to followup with receiveMessage if a message is found
//caller should handle stop separately
void MessageHandler::waitForMessage(){
    _waitForMessageMutex.lock();
}

//waitForMessageUntil waits until a message is on the stack or timeoutTime is reached
//returns true if a message is received, false if timeoutTime is reached
//also stops waiting and returns true if stop is called
//Blocks the thread while waiting
//Requires caller to followup with receiveMessage if a message is found
//caller should handle stop seperately
bool MessageHandler::waitForMessageUntil(std::chrono::steady_clock::time_point timeoutTime){
    return _waitForMessageMutex.try_lock_until(timeoutTime);
}

//stop is used to stop waiting for messages without adding a message
void MessageHandler::stop(){
    _waitForMessageMutex.unlock();
}