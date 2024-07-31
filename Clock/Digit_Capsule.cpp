#include "Digit_Capsule.h"

Digit_Capsule::Digit_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _base = 10;
}

int Digit_Capsule::getId(){
    return _id;
}

void Digit_Capsule::handleMessage(Message message){
    if(std::holds_alternative<IncMessage>(message)){
        IncMessage iMessage = std::get<IncMessage>(message);
        handleMessage(iMessage);
    }
    else if(std::holds_alternative<SetBaseMessage>(message)){
        SetBaseMessage sMessage = std::get<SetBaseMessage>(message);
        handleMessage(sMessage);
    }
    else{
        throw std::invalid_argument("Clock_Capsule unable to handle that message");
    }
}

Message Digit_Capsule::handleInvokeMessage(Message request){
    if(std::holds_alternative<RequestDigitMessage>(request)){
        RequestDigitMessage rMessage = std::get<RequestDigitMessage>(request);
        return handleInvokeMessage(rMessage);
    }
    else{
        throw std::invalid_argument("Clock_Capsule unable to handle that invokeMessage");
    }
}

void Digit_Capsule::connect(int clockId){
    _clockId = clockId;
}

void Digit_Capsule::start(){
    _state = Zero;
}

void Digit_Capsule::sendCarryMessage(int toId){
    CarryMessage outMessage;
    outMessage.fromId = _id;
    SendMessage sendMessage;
    sendMessage.toId = toId;
    sendMessage.message = outMessage;
    _messageHandlerPtr->sendMessage(sendMessage);
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

void Digit_Capsule::handleMessage(SetBaseMessage inMessage){
    _base = inMessage.base;
}

Message Digit_Capsule::handleInvokeMessage(RequestDigitMessage inMessage){
    RespondDigitMessage outMessage;
    outMessage.fromId = _id;
    outMessage.value = _state;
    return outMessage;
}