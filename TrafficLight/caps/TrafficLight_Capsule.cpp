#include "TrafficLight_Capsule.h"
#include "CapsuleRunner.h"

TrafficLight_Capsule::TrafficLight_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
}

int TrafficLight_Capsule::getId(){
    return _id;
}

void TrafficLight_Capsule::start(){
    _state = Red;
    _timerRunnerPtr->informEvery(_id, std::chrono::seconds(2));
}

void TrafficLight_Capsule::handleMessage(Message message){
    if(std::holds_alternative<TimeoutMessage>(message)){
        handleTimeout(std::get<TimeoutMessage>(message));
    }
    else{
        throw std::invalid_argument("TrafficLight_Capsule unable to handle that message");
    }
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