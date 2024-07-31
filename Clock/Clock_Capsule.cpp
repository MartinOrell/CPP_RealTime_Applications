#include "Clock_Capsule.h"
#include "CapsuleRunner.h"

Clock_Capsule::Clock_Capsule(int id, MessageHandler<SendMessage>* messageHandlerPtr, TimerThread* timerThreadPtr, CapsuleRunner* capsuleRunnerPtr, int speedMultiplier){
    _id = id;
    _messageHandlerPtr = messageHandlerPtr;
    _timerThreadPtr = timerThreadPtr;
    _capsuleRunnerPtr = capsuleRunnerPtr;
    _tickPeriod = std::chrono::nanoseconds(1000000000/speedMultiplier);
    if(_tickPeriod <= std::chrono::nanoseconds(0)){
        throw std::range_error("tickPeriod is too low, try a lower speedMultiplier");
    }
}

int Clock_Capsule::getId(){
    return _id;
}

void Clock_Capsule::handleMessage(Message message){
    if(std::holds_alternative<NoContentMessage>(message)){
        NoContentMessage emptyMessage = std::get<NoContentMessage>(message);
        if(emptyMessage == NoContentMessage::RequestTimeMessage){
            handleRequestTimeMessage();
        }
        else{
            throw std::invalid_argument("Clock_Capsule received emptyMessage of wrong type");
        }
    }
    else if(std::holds_alternative<TimeoutMessage>(message)){
        TimeoutMessage tMessage = std::get<TimeoutMessage>(message);
        handleTimeout(tMessage);
    }
    else if(std::holds_alternative<CarryMessage>(message)){
        CarryMessage cMessage = std::get<CarryMessage>(message);
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

void Clock_Capsule::start(){
    _state = SecondTicker;
    
    SetBaseMessage outMessage1;
    outMessage1.toId = _second10DigitCapsuleId;
    outMessage1.base = 6;
    SendMessage sendMessage1;
    sendMessage1.toId = _second10DigitCapsuleId;
    sendMessage1.message = outMessage1;
    _messageHandlerPtr->sendMessage(sendMessage1);

    SetBaseMessage outMessage2;
    outMessage2.toId = _minute10DigitCapsuleId;
    outMessage2.base = 6;
    SendMessage sendMessage2;
    sendMessage2.toId = _minute10DigitCapsuleId;
    sendMessage2.message = outMessage2;
    _messageHandlerPtr->sendMessage(sendMessage2);

    SetBaseMessage outMessage3;
    outMessage3.toId = _hour10DigitCapsuleId;
    outMessage3.base = 3;
    SendMessage sendMessage3;
    sendMessage3.toId = _hour10DigitCapsuleId;
    sendMessage3.message = outMessage3;
    _messageHandlerPtr->sendMessage(sendMessage3);

    _tickerId = _timerThreadPtr->informEvery(_id, _tickPeriod);
}

void Clock_Capsule::handleTimeout(TimeoutMessage timeoutMessage){
    switch(_state){
        case SecondTicker:
            {
                IncMessage outMessage;
                outMessage.toId = _second1DigitCapsuleId;
                SendMessage sendMessage;
                sendMessage.toId = outMessage.toId;
                sendMessage.message = outMessage;
                _messageHandlerPtr->sendMessage(sendMessage);
                if(timeoutMessage.timeouts > 1){
                    _state = Second10Ticker;
                    _timerThreadPtr->cancelTimer(_tickerId);
                    _tickPeriod *= 10;
                    _tickerId = _timerThreadPtr->informEvery(_id, _tickPeriod);
                     std::cout << "Ticking in 10 seconds interval due to "
                    << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
                }
            }
            break;
        case Second10Ticker:
            {
                IncMessage outMessage;
                outMessage.toId = _second10DigitCapsuleId;
                SendMessage sendMessage;
                sendMessage.toId = _second10DigitCapsuleId;
                sendMessage.message = outMessage;
                _messageHandlerPtr->sendMessage(sendMessage);
                if(timeoutMessage.timeouts > 1){
                    _state = MinuteTicker;
                    _timerThreadPtr->cancelTimer(_tickerId);
                    _tickPeriod *= 6;
                    _tickerId = _timerThreadPtr->informEvery(_id, _tickPeriod);
                     std::cout << "Ticking in 1 minute interval due to "
                    << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
                }
            }
            break;
        case MinuteTicker:
            {
                IncMessage outMessage;
                outMessage.toId = _minute1DigitCapsuleId;
                SendMessage sendMessage;
                sendMessage.toId = _minute1DigitCapsuleId;
                sendMessage.message = outMessage;
                _messageHandlerPtr->sendMessage(sendMessage);
                if(timeoutMessage.timeouts > 1){
                    _state = Minute10Ticker;
                    _timerThreadPtr->cancelTimer(_tickerId);
                    _tickPeriod *= 10;
                    _tickerId = _timerThreadPtr->informEvery(_id, _tickPeriod);
                     std::cout << "Ticking in 10 minutes interval due to "
                    << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
                }
            }
            break;
        case Minute10Ticker:
            {
                IncMessage outMessage;
                outMessage.toId = _minute10DigitCapsuleId;
                SendMessage sendMessage;
                sendMessage.toId = _minute10DigitCapsuleId;
                sendMessage.message = outMessage;
                _messageHandlerPtr->sendMessage(sendMessage);
                if(timeoutMessage.timeouts > 1){
                    _state = HourTicker;
                    _timerThreadPtr->cancelTimer(_tickerId);
                    _tickPeriod *= 6;
                    _tickerId = _timerThreadPtr->informEvery(_id, _tickPeriod);
                     std::cout << "Ticking in 1 hour interval due to "
                    << timeoutMessage.timeouts-1 << " missed timeouts." << std::endl;
                }
            }
            break;
        case HourTicker:
            {
                IncMessage outMessage;
                outMessage.toId = _hour1DigitCapsuleId;
                SendMessage sendMessage;
                sendMessage.toId = _hour1DigitCapsuleId;
                sendMessage.message = outMessage;
                _messageHandlerPtr->sendMessage(sendMessage);
            }
            break;
    }
}

void Clock_Capsule::handleMessage(CarryMessage inMessage){
    if(inMessage.fromId == _second1DigitCapsuleId){
        IncMessage outMessage;
        outMessage.toId = _second10DigitCapsuleId;
        SendMessage sendMessage;
        sendMessage.toId = _second10DigitCapsuleId;
        sendMessage.message = outMessage;
        _messageHandlerPtr->sendMessage(sendMessage);
    }
    else if(inMessage.fromId == _second10DigitCapsuleId){
        IncMessage outMessage;
        outMessage.toId = _minute1DigitCapsuleId;
        SendMessage sendMessage;
        sendMessage.toId = _minute1DigitCapsuleId;
        sendMessage.message = outMessage;
        _messageHandlerPtr->sendMessage(sendMessage);
    }
    else if(inMessage.fromId == _minute1DigitCapsuleId){
        IncMessage outMessage;
        outMessage.toId = _minute10DigitCapsuleId;
        SendMessage sendMessage;
        sendMessage.toId = _minute10DigitCapsuleId;
        sendMessage.message = outMessage;
        _messageHandlerPtr->sendMessage(sendMessage);
    }
    else if(inMessage.fromId == _minute10DigitCapsuleId){
        IncMessage outMessage;
        outMessage.toId = _hour1DigitCapsuleId;
        SendMessage sendMessage;
        sendMessage.toId = _hour1DigitCapsuleId;
        sendMessage.message = outMessage;
        _messageHandlerPtr->sendMessage(sendMessage);
    }
    else if(inMessage.fromId == _hour1DigitCapsuleId){
        //If we get to 20 hours, then next 10x carry should be at 24 (4)
        RequestDigitMessage request;
        request.toId = _hour10DigitCapsuleId;
        SendMessage sendRequest;
        sendRequest.toId = _hour10DigitCapsuleId;
        sendRequest.message = request;
        Message message = _capsuleRunnerPtr->invokeMessage(sendRequest);
        assert(std::holds_alternative<RespondDigitMessage>(message));
        int hour10 = std::get<RespondDigitMessage>(message).value;
        if(hour10 == 1){ //Will be 2 after inc
            SetBaseMessage outMessage;
            outMessage.toId = _hour1DigitCapsuleId;
            outMessage.base = 4;
            SendMessage sendMessage;
            sendMessage.toId = _hour1DigitCapsuleId;
            sendMessage.message = outMessage;
            _messageHandlerPtr->sendMessage(sendMessage);
        }

        IncMessage outMessage;
        outMessage.toId = _hour10DigitCapsuleId;
        SendMessage sendMessage;
        sendMessage.toId = _hour10DigitCapsuleId;
        sendMessage.message = outMessage;
        _messageHandlerPtr->sendMessage(sendMessage);
    }
    else if(inMessage.fromId == _hour10DigitCapsuleId){
        SetBaseMessage outMessage;
        outMessage.toId = _hour1DigitCapsuleId;
        outMessage.base = 10;
        SendMessage sendMessage;
        sendMessage.toId = _hour1DigitCapsuleId;
        sendMessage.message = outMessage;
        _messageHandlerPtr->sendMessage(sendMessage);
    }
    else{
        throw std::out_of_range("Clock does not handle carry message from capsule id: " + inMessage.fromId);
    }
}

void Clock_Capsule::handleRequestTimeMessage(){

    RequestDigitMessage second1Request{_second1DigitCapsuleId};
    SendMessage sendRequest1;
    sendRequest1.toId = _second1DigitCapsuleId;
    sendRequest1.message = second1Request;
    Message message = _capsuleRunnerPtr->invokeMessage(sendRequest1);
    assert(std::holds_alternative<RespondDigitMessage>(message));
    int sec1 = std::get<RespondDigitMessage>(message).value;

    RequestDigitMessage second10Request{_second10DigitCapsuleId};
    SendMessage sendRequest2;
    sendRequest2.toId = _second10DigitCapsuleId;
    sendRequest2.message = second10Request;
    message = _capsuleRunnerPtr->invokeMessage(sendRequest2);
    assert(std::holds_alternative<RespondDigitMessage>(message));
    int sec10 = std::get<RespondDigitMessage>(message).value;

    RequestDigitMessage minute1Request{_minute1DigitCapsuleId};
    SendMessage sendRequest3;
    sendRequest3.toId = _minute1DigitCapsuleId;
    sendRequest3.message = minute1Request;
    message = _capsuleRunnerPtr->invokeMessage(sendRequest3);
    assert(std::holds_alternative<RespondDigitMessage>(message));
    int min1 = std::get<RespondDigitMessage>(message).value;

    RequestDigitMessage minute10Request{_minute10DigitCapsuleId};
    SendMessage sendRequest4;
    sendRequest4.toId = _minute10DigitCapsuleId;
    sendRequest4.message = minute10Request;
    message = _capsuleRunnerPtr->invokeMessage(sendRequest4);
    assert(std::holds_alternative<RespondDigitMessage>(message));
    int min10 = std::get<RespondDigitMessage>(message).value;

    RequestDigitMessage hour1Request{_hour1DigitCapsuleId};
    SendMessage sendRequest5;
    sendRequest5.toId = _hour1DigitCapsuleId;
    sendRequest5.message = hour1Request;
    message = _capsuleRunnerPtr->invokeMessage(sendRequest5);
    assert(std::holds_alternative<RespondDigitMessage>(message));
    int hour1 = std::get<RespondDigitMessage>(message).value;

    RequestDigitMessage hour10Request{_hour10DigitCapsuleId};
    SendMessage sendMessage6;
    sendMessage6.toId = _hour10DigitCapsuleId;
    sendMessage6.message = hour10Request;
    message = _capsuleRunnerPtr->invokeMessage(sendMessage6);
    assert(std::holds_alternative<RespondDigitMessage>(message));
    int hour10 = std::get<RespondDigitMessage>(message).value;

    RespondTimeMessage outMessage;
    outMessage.time =
        std::to_string(hour10) +
        std::to_string(hour1) +
        ":" +
        std::to_string(min10) +
        std::to_string(min1) +
        ":" +
        std::to_string(sec10) +
        std::to_string(sec1);
    SendMessage sendMessage;
    sendMessage.toId = _mainId;
    sendMessage.message = outMessage;
    _messageHandlerPtr->sendMessage(sendMessage);
}