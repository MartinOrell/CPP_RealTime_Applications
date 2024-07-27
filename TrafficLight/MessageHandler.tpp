
template<typename T>
MessageHandler<T>::MessageHandler(){
    _waitForMessageMutex.lock();
}

template<typename T>
void MessageHandler<T>::sendMessage(T message){
    _mutex.lock();
    _messageStack.push_back(message);
    _mutex.unlock();
    _waitForMessageMutex.unlock();
}

//receiveMessage returns the top message on the stack
//Caller should check with hasMessage(), WaitForMessage() or WaitForMessageUntil()
//before calling this function
template<typename T>
T MessageHandler<T>::receiveMessage(){
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

//hasMessage returns true if a message is on the stack
//also returns true if stop is called
//Does not block
//Requires caller to followup with receiveMessage if a message is found
template<typename T>
bool MessageHandler<T>::hasMessage(){
    return _waitForMessageMutex.try_lock();
}

//waitForMessage waits until a message is on the stack
//also stops waiting if stop is called
//Blocks the thread while waiting
//Requires caller to followup with receiveMessage if a message is found
//caller should handle stop separately
template<typename T>
void MessageHandler<T>::waitForMessage(){
    _waitForMessageMutex.lock();
}

//waitForMessageUntil waits until a message is on the stack or timeoutTime is reached
//returns true if a message is received, false if timeoutTime is reached
//also stops waiting and returns true if stop is called
//Blocks the thread while waiting
//Requires caller to followup with receiveMessage if a message is found
//caller should handle stop seperately
template<typename T>
bool MessageHandler<T>::waitForMessageUntil(std::chrono::steady_clock::time_point timeoutTime){
    return _waitForMessageMutex.try_lock_until(timeoutTime);
}

//stop is used to stop waiting for messages without adding a message
template<typename T>
void MessageHandler<T>::stop(){
    _waitForMessageMutex.unlock();
}