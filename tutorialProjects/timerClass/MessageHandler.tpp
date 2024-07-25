
template<typename T>
MessageHandler<T>::MessageHandler(){
    _waitForMessageMutex.lock();
}

template<typename T>
void MessageHandler<T>::addMessage(T message){
    _mutex.lock();
    _messageStack.push_back(message);
    _mutex.unlock();
    _waitForMessageMutex.unlock();
}

//hasMessage returns true if a message is received
//also returns true if stop is called
//Does not block
//Requires caller to followup with popping the message if true
template<typename T>
bool MessageHandler<T>::hasMessage(){
    return _waitForMessageMutex.try_lock();
}

//waitForMessage waits until a message is received
//also stops waiting if stop is called
//Blocks the thread while waiting
//Requires caller to followup with popping the message if a message is received
//caller should handle stop separately
template<typename T>
void MessageHandler<T>::waitForMessage(){
    _waitForMessageMutex.lock();
}

//waitForMessageUntil waits until a message is received or timeoutTime is reached
//returns true if a message is received, false if timeoutTime is reached
//also stops waiting and returns true if stop is called
//Blocks the thread while waiting
//Requires caller to followup with popping message if true
//caller should handle stop seperately
template<typename T>
bool MessageHandler<T>::waitForMessageUntil(std::chrono::steady_clock::time_point timeoutTime){
    return _waitForMessageMutex.try_lock_until(timeoutTime);
}

template<typename T>
T MessageHandler<T>::popMessage(){
    assert(_messageStack.size() > 0);
    _mutex.lock();
    T message = _messageStack.back();
    _messageStack.pop_back();
    if(_messageStack.size() > 0)
    {
        _waitForMessageMutex.unlock();
    }
    _mutex.unlock();
    return message;
}

//stop is used to stop waiting for messages without adding a message
template<typename T>
void MessageHandler<T>::stop(){
    _waitForMessageMutex.unlock();
}