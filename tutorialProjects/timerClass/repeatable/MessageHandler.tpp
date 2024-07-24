
template<typename T>
MessageHandler<T>::MessageHandler(){}

template<typename T>
void MessageHandler<T>::addMessage(T message){
    _mutex.lock();
    _messageStack.push_back(message);
    _mutex.unlock();
}

template<typename T>
bool MessageHandler<T>::hasMessage(){
    return !_messageStack.empty();
}

template<typename T>
T MessageHandler<T>::popMessage(){
    _mutex.lock();
    T message = _messageStack.back();
    _messageStack.pop_back();
    _mutex.unlock();
    return message;
}