#include "HelloWorld_Capsule.h"
#include "CapsuleRunner.h"

HelloWorld_Capsule::HelloWorld_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
}

int HelloWorld_Capsule::getId(){
    return _id;
}

void HelloWorld_Capsule::start(){
    _state = S1;
    _timerRunnerPtr->informIn(_id, std::chrono::seconds(1));
}

void HelloWorld_Capsule::handleMessage(mrt::Message message){
    if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        handleTimeout(std::get<mrt::TimeoutMessage>(message));
    }
    else{
        throw std::invalid_argument("HelloWorld_Capsule unable to handle that message");
    }
}

void HelloWorld_Capsule::handleTimeout(mrt::TimeoutMessage timeoutMessage){
    switch(_state){
        case S1:
            {
                _state = S2;
                std::cout << "Hello World!" << std::endl;
                _capsuleRunnerPtr->stop();
            }
            break;
        default:
            throw std::runtime_error("Timeout not handled in this state");
            break;
    }
}