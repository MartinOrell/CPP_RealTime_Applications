#include "Clock_Capsule.h"

#include "CapsuleRunner.h"

#include <chrono>
#include <stdexcept>
#include <cassert>
#include <iostream>

Clock_Capsule::Clock_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, int speedMultiplier){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _timerRunnerPtr = timerRunnerPtr;
    _tickPeriod = std::chrono::nanoseconds(1000000000/speedMultiplier);
    if(_tickPeriod <= std::chrono::nanoseconds(0)){
        throw std::range_error("tickPeriod is too low, try a lower speedMultiplier");
    }
}

int Clock_Capsule::getId(){
    return _id;
}

void Clock_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::VoidMessage>(message)){
        mrt::VoidMessage voidMessage = std::get<mrt::VoidMessage>(message);
        if(voidMessage == mrt::VoidMessage::RequestTimeMessage){
            handleRequestTimeMessage();
        }
        else{
            throw std::invalid_argument("Clock_Capsule received emptyMessage of wrong type");
        }
    }
    else if(std::holds_alternative<mrt::TimeoutMessage>(message)){
        mrt::TimeoutMessage tMessage = std::get<mrt::TimeoutMessage>(message);
        handleTimeout(tMessage);
    }
    else if(std::holds_alternative<mrt::CarryMessage>(message)){
        mrt::CarryMessage cMessage = std::get<mrt::CarryMessage>(message);
        handleMessage(cMessage);
    }
    else{
        throw std::invalid_argument("Clock_Capsule unable to handle that message");
    }
}

void Clock_Capsule::connectMain(int mainId){
    _mainId = mainId;
}

void Clock_Capsule::connectSecond1Digit(int digitId){
    _second1DigitCapsuleId = digitId;
}

void Clock_Capsule::connectSecond10Digit(int digitId){
    _second10DigitCapsuleId = digitId;
}

void Clock_Capsule::connectMinute1Digit(int digitId){
    _minute1DigitCapsuleId = digitId;
}

void Clock_Capsule::connectMinute10Digit(int digitId){
    _minute10DigitCapsuleId = digitId;
}

void Clock_Capsule::connectHour1Digit(int digitId){
    _hour1DigitCapsuleId = digitId;
}

void Clock_Capsule::connectHour10Digit(int digitId){
    _hour10DigitCapsuleId = digitId;
}

void Clock_Capsule::sendRespondTimeMessage(int toId, std::string time){
    mrt::RespondTimeMessage outMessage;
    outMessage.time = time;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Clock_Capsule::sendIncMessage(int toId){
    mrt::VoidMessage outMessage = mrt::VoidMessage::IncMessage;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Clock_Capsule::sendSetBaseMessage(int toId, int base){
    mrt::SetBaseMessage outMessage;
    outMessage.base = base;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}
mrt::RespondDigitMessage Clock_Capsule::invokeRequestDigitMessage(int toId){
    mrt::VoidMessage request = mrt::VoidMessage::RequestDigitMessage;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = request;
    mrt::Message receivedMessage = _capsuleRunnerPtr->invokeMessage(sendMessage);
    assert(std::holds_alternative<mrt::RespondDigitMessage>(receivedMessage));
    return std::get<mrt::RespondDigitMessage>(receivedMessage);
}

void Clock_Capsule::start(){
    _state = SecondTicker;
    
    sendSetBaseMessage(_second10DigitCapsuleId, 6);
    sendSetBaseMessage(_minute10DigitCapsuleId, 6);
    sendSetBaseMessage(_hour10DigitCapsuleId, 3);

    _tickerId = _timerRunnerPtr->informEvery(_id, _tickPeriod);
}

void Clock_Capsule::handleTimeout(const mrt::TimeoutMessage& timeoutMessage){
    switch(_state){
        case SecondTicker:
            sendIncMessage(_second1DigitCapsuleId);
            if(timeoutMessage.timeouts > 1){
                _state = Second10Ticker;
                _timerRunnerPtr->cancelTimer(_tickerId);
                _tickPeriod *= 10;
                _tickerId = _timerRunnerPtr->informEvery(_id, _tickPeriod);
                    std::cout << "Ticking in 10 seconds interval due to "
                << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
            }
            break;
        case Second10Ticker:
            sendIncMessage(_second10DigitCapsuleId);
            if(timeoutMessage.timeouts > 1){
                _state = MinuteTicker;
                _timerRunnerPtr->cancelTimer(_tickerId);
                _tickPeriod *= 6;
                _tickerId = _timerRunnerPtr->informEvery(_id, _tickPeriod);
                    std::cout << "Ticking in 1 minute interval due to "
                << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
            }
            break;
        case MinuteTicker:
            sendIncMessage(_minute1DigitCapsuleId);
            if(timeoutMessage.timeouts > 1){
                _state = Minute10Ticker;
                _timerRunnerPtr->cancelTimer(_tickerId);
                _tickPeriod *= 10;
                _tickerId = _timerRunnerPtr->informEvery(_id, _tickPeriod);
                    std::cout << "Ticking in 10 minutes interval due to "
                << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
            }
            break;
        case Minute10Ticker:
            sendIncMessage(_minute10DigitCapsuleId);
            if(timeoutMessage.timeouts > 1){
                _state = HourTicker;
                _timerRunnerPtr->cancelTimer(_tickerId);
                _tickPeriod *= 6;
                _tickerId = _timerRunnerPtr->informEvery(_id, _tickPeriod);
                    std::cout << "Ticking in 1 hour interval due to "
                << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
            }
            break;
        case HourTicker:
            sendIncMessage(_hour10DigitCapsuleId);
            break;
    }
}

void Clock_Capsule::handleMessage(const mrt::CarryMessage& inMessage){
    if(inMessage.fromId == _second1DigitCapsuleId){
        sendIncMessage(_second10DigitCapsuleId);
    }
    else if(inMessage.fromId == _second10DigitCapsuleId){
        sendIncMessage(_minute1DigitCapsuleId);
    }
    else if(inMessage.fromId == _minute1DigitCapsuleId){
        sendIncMessage(_minute10DigitCapsuleId);
    }
    else if(inMessage.fromId == _minute10DigitCapsuleId){
        sendIncMessage(_hour1DigitCapsuleId);
    }
    else if(inMessage.fromId == _hour1DigitCapsuleId){
        //If we get to 20 hours, then next 10x carry should be at 24 (4)
        int hour10 = invokeRequestDigitMessage(_hour10DigitCapsuleId).value;
        if(hour10 == 1){ //Will be 2 after inc
            sendSetBaseMessage(_hour1DigitCapsuleId, 4);
        }
        sendIncMessage(_hour10DigitCapsuleId);
    }
    else if(inMessage.fromId == _hour10DigitCapsuleId){
        sendSetBaseMessage(_hour1DigitCapsuleId,10);
    }
    else{
        throw std::out_of_range("Clock does not handle carry message from capsule id: " + inMessage.fromId);
    }
}

void Clock_Capsule::handleRequestTimeMessage(){

    int sec1 = invokeRequestDigitMessage(_second1DigitCapsuleId).value;
    int sec10 = invokeRequestDigitMessage(_second10DigitCapsuleId).value;
    int min1 = invokeRequestDigitMessage(_minute1DigitCapsuleId).value;
    int min10 = invokeRequestDigitMessage(_minute10DigitCapsuleId).value;
    int hour1 = invokeRequestDigitMessage(_hour1DigitCapsuleId).value;
    int hour10 = invokeRequestDigitMessage(_hour10DigitCapsuleId).value;

    std::string time =
        std::to_string(hour10) +
        std::to_string(hour1) +
        ":" +
        std::to_string(min10) +
        std::to_string(min1) +
        ":" +
        std::to_string(sec10) +
        std::to_string(sec1);

    sendRespondTimeMessage(_mainId, time);
}