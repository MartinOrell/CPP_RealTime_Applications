#include "Digit_Capsule.h"

#include "CapsuleRunner.h"

#include <stdexcept>

Digit_Capsule::Digit_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr){
    _id = id;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _base = 10;
}

int Digit_Capsule::getId(){
    return _id;
}

void Digit_Capsule::handleMessage(const mrt::Message& message){
    if(std::holds_alternative<mrt::VoidMessage>(message)){
        if(std::get<mrt::VoidMessage>(message) == mrt::VoidMessage::IncMessage){
            handleIncMessage();
        }
        else{
            throw std::invalid_argument("Digit_Capsule unable to handle that voidMessage");
        }
    }
    else if(std::holds_alternative<mrt::SetBaseMessage>(message)){
        mrt::SetBaseMessage sMessage = std::get<mrt::SetBaseMessage>(message);
        handleMessage(sMessage);
    }
    else{
        throw std::invalid_argument("Digit_Capsule unable to handle that message");
    }
}

mrt::Message Digit_Capsule::handleInvokeMessage(const mrt::Message& request){
    if(std::holds_alternative<mrt::VoidMessage>(request)){
        if(std::get<mrt::VoidMessage>(request) == mrt::VoidMessage::RequestDigitMessage){
            return handleInvokeRequestDigitMessage();
        }
        else{
            throw std::invalid_argument("Digit_Capsule unable to invoke that voidMessage");
        }
    }
    else{
        throw std::invalid_argument("Digit_Capsule unable to handle that invokeMessage");
    }
}

void Digit_Capsule::connect(int clockId){
    _clockId = clockId;
}

void Digit_Capsule::start(){
    _state = Zero;
}

void Digit_Capsule::sendCarryMessage(int toId){
    mrt::CarryMessage outMessage;
    outMessage.fromId = _id;
    mrt::SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _capsuleRunnerPtr->sendMessage(sendMessage);
}

void Digit_Capsule::handleIncMessage(){
    switch(_state){
        case Zero:
            _state = One;
            break;
        case One:
            _state = Two;
            break;
        case Two:
            if(_base == 3){
                _state = Zero;
                sendCarryMessage(_clockId);
            }
            else{
                _state = Three;
            }
            break;
        case Three:
            if(_base == 4){
                _state = Zero;
                sendCarryMessage(_clockId);
            }
            else{
                _state = Four;
            }
            break;
        case Four:
            _state = Five;
            break;
        case Five:
            if(_base == 6){
                _state = Zero;
                sendCarryMessage(_clockId);
            }
            else{
                _state = Six;
            }
            break;
        case Six:
            _state = Seven;
            break;
        case Seven:
            _state = Eight;
            break;
        case Eight:
            _state = Nine;
            break;
        case Nine:
            _state = Zero;
            sendCarryMessage(_clockId);
            break;
    }
}

void Digit_Capsule::handleMessage(mrt::SetBaseMessage inMessage){
    _base = inMessage.base;
}

mrt::Message Digit_Capsule::handleInvokeRequestDigitMessage(){
    mrt::RespondDigitMessage outMessage;
    outMessage.fromId = _id;
    outMessage.value = _state;
    return outMessage;
}