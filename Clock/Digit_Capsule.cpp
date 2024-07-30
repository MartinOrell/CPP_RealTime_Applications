#include "Digit_Capsule.h"

Digit_Capsule::Digit_Capsule(int id, MessageHandler<Message>*messageHandlerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _base = 10;
}

int Digit_Capsule::getId(){
    return _id;
}

void Digit_Capsule::connect(int clockId){
    _clockId = clockId;
}

void Digit_Capsule::start(){
    _state = Zero;
}

void Digit_Capsule::handleMessage(IncMessage inMessage){
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
                CarryMessage outMessage;
                outMessage.fromId = _id;
                _messageHandlerPtr->sendMessage(outMessage);
            }
            else{
                _state = Three;
            }
            break;
        case Three:
            if(_base == 4){
                _state = Zero;
                CarryMessage outMessage;
                outMessage.fromId = _id;
                _messageHandlerPtr->sendMessage(outMessage);
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
                CarryMessage outMessage;
                outMessage.fromId = _id;
                _messageHandlerPtr->sendMessage(outMessage);
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
            CarryMessage outMessage;
            outMessage.fromId = _id;
            _messageHandlerPtr->sendMessage(outMessage);
            break;
    }
}

void Digit_Capsule::handleMessage(SetBaseMessage inMessage){
    _base = inMessage.base;
}

Message Digit_Capsule::handleInvokeMessage(RequestDigitMessage inMessage){
    RespondDigitMessage outMessage;
    outMessage.fromId = _id;
    outMessage.value = _state;
    return outMessage;
}