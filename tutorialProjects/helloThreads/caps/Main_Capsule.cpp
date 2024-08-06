#include "Main_Capsule.h"
#include "CapsuleRunner.h"

Main_Capsule::Main_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
    _count = 0;
}

int Main_Capsule::getId(){
    return _id;
}

void Main_Capsule::start(){
    std::cout << "Main: Start repeatTimer every second\n";
    _updateTimerId = _timerRunnerPtr->informEvery(_id, std::chrono::seconds(1));
    _endTimerId = _timerRunnerPtr->informIn(_id, std::chrono::seconds(12));
}
        
void Main_Capsule::handleMessage(Message message){
    if(std::holds_alternative<TimeoutMessage>(message)){
        TimeoutMessage timeoutMessage = std::get<TimeoutMessage>(message);
        if(timeoutMessage.timerId == _updateTimerId){
            handleRepeatTimerTimeout(timeoutMessage.timeouts);
        }
        else if(timeoutMessage.timerId == _endTimerId){
            handleEndTimerTimeout();
        }
        else{
            throw std::invalid_argument("Main_Capsule unable to handle that timeout");
        }
    }
    else{
        throw std::invalid_argument("Main_Capsule unable to handle that message");
    }
}

void Main_Capsule::handleRepeatTimerTimeout(int timeouts){
    _count++;
    if(timeouts > 1){
        std::cout << "Main: Missed timeouts: " + std::to_string(timeouts-1) + "\n"; 
    }
    std::cout << "Main: Count: " + std::to_string(_count) + "\n";
}

void Main_Capsule::handleEndTimerTimeout(){
    _capsuleRunnerPtr->stop();
}