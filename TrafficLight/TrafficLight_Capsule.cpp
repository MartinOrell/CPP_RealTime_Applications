#include "TrafficLight_Capsule.h"

TrafficLight_Capsule::TrafficLight_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, TimerThread* timerThreadPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
}

void TrafficLight_Capsule::start(){
    _state = Red;
    _timerThreadPtr->informEvery(_id, std::chrono::seconds(2));
}

void TrafficLight_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    switch(_state){
        case Red:
            {
                _state = Green;
                std::cout << "Green" << std::endl;
            }
            break;
        case Green:
            {
                _state = Yellow;
                std::cout << "Yellow" << std::endl;
            }
            break;
        case Yellow:
            {
                _state = Red;
                std::cout << "Red" << std::endl;
            }
            break;
    }
}