#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(TimerThread* timerThreadPtr, MessageHandler<Message>* messageHandlerPtr, std::chrono::steady_clock::duration timeoutTime, int fps, int speedMultiplier)
:   _nextCapsuleId{0},
    _main{_nextCapsuleId++, messageHandlerPtr, timerThreadPtr, timeoutTime, fps},
    _clock{_nextCapsuleId++, messageHandlerPtr, timerThreadPtr, this, speedMultiplier},
    _second1Digit{_nextCapsuleId++, messageHandlerPtr},
    _second10Digit{_nextCapsuleId++, messageHandlerPtr},
    _minute1Digit{_nextCapsuleId++, messageHandlerPtr},
    _minute10Digit{_nextCapsuleId++, messageHandlerPtr},
    _hour1Digit{_nextCapsuleId++, messageHandlerPtr},
    _hour10Digit{_nextCapsuleId++, messageHandlerPtr},
    _messageHandlerPtr{messageHandlerPtr}{

    _main.connect(_clock.getId());
    _clock.connectMain(_main.getId());
    _clock.connectSecond1Digit(_second1Digit.getId());
    _second1Digit.connect(_clock.getId());
    _clock.connectSecond10Digit(_second10Digit.getId());
    _second10Digit.connect(_clock.getId());
    _clock.connectMinute1Digit(_minute1Digit.getId());
    _minute1Digit.connect(_clock.getId());
    _clock.connectMinute10Digit(_minute10Digit.getId());
    _minute10Digit.connect(_clock.getId());
    _clock.connectHour1Digit(_hour1Digit.getId());
    _hour1Digit.connect(_clock.getId());
    _clock.connectHour10Digit(_hour10Digit.getId());
    _hour10Digit.connect(_clock.getId());
}

void CapsuleRunner::run(){
    
    _main.start();
    _clock.start();
    _second1Digit.start();
    _second10Digit.start();
    _minute1Digit.start();
    _minute10Digit.start();
    _hour1Digit.start();
    _hour10Digit.start();

    while(true){
        _messageHandlerPtr->waitForMessage();
        Message message = _messageHandlerPtr->receiveMessage();
        if(std::holds_alternative<NoContentMessage>(message)){
            NoContentMessage emptyMessage = std::get<NoContentMessage>(message);
            if(emptyMessage == NoContentMessage::EndMessage){
                return;
            }
            else if(emptyMessage == NoContentMessage::RequestTimeMessage){
                _clock.handleRequestTimeMessage();
            }
            else{
                throw std::invalid_argument("CapsuleRunner received emptyMessage of wrong type");
            }
        }
        else if(std::holds_alternative<TimeoutMessage>(message)){
            TimeoutMessage tMessage = std::get<TimeoutMessage>(message);
            if(tMessage.toId == _main.getId()){
                _main.handleTimeout(tMessage);
            }
            else if(tMessage.toId == _clock.getId()){
                _clock.handleTimeout(tMessage);
            }
            else{
                throw std::invalid_argument("CapsuleRunner unable to deal with timeout to capsule id: " + std::to_string(tMessage.toId));
            }
        }
        else if(std::holds_alternative<RespondTimeMessage>(message)){
            RespondTimeMessage rMessage = std::get<RespondTimeMessage>(message);
            _main.handleMessage(rMessage);
        }
        else if(std::holds_alternative<IncMessage>(message)){
            IncMessage iMessage = std::get<IncMessage>(message);
            if(iMessage.toId == _second1Digit.getId()){
                _second1Digit.handleMessage(iMessage);
            }
            else if(iMessage.toId == _second10Digit.getId()){
                _second10Digit.handleMessage(iMessage);
            }
            else if(iMessage.toId == _minute1Digit.getId()){
                _minute1Digit.handleMessage(iMessage);
            }
            else if(iMessage.toId == _minute10Digit.getId()){
                _minute10Digit.handleMessage(iMessage);
            }
            else if(iMessage.toId == _hour1Digit.getId()){
                _hour1Digit.handleMessage(iMessage);
            }
            else if(iMessage.toId == _hour10Digit.getId()){
                _hour10Digit.handleMessage(iMessage);
            }
            else{
                throw std::invalid_argument("CapsuleRunner unable to deal with incMessage to capsule id: " + std::to_string(iMessage.toId));
            }
        }
        else if(std::holds_alternative<CarryMessage>(message)){
            CarryMessage cMessage = std::get<CarryMessage>(message);
            _clock.handleMessage(cMessage);
        }
        else if(std::holds_alternative<SetBaseMessage>(message)){
            SetBaseMessage sMessage = std::get<SetBaseMessage>(message);
            if(sMessage.toId == _second1Digit.getId()){
                _second1Digit.handleMessage(sMessage);
            }
            else if(sMessage.toId == _second10Digit.getId()){
                _second10Digit.handleMessage(sMessage);
            }
            else if(sMessage.toId == _minute1Digit.getId()){
                _minute1Digit.handleMessage(sMessage);
            }
            else if(sMessage.toId == _minute10Digit.getId()){
                _minute10Digit.handleMessage(sMessage);
            }
            else if(sMessage.toId == _hour1Digit.getId()){
                _hour1Digit.handleMessage(sMessage);
            }
            else if(sMessage.toId == _hour10Digit.getId()){
                _hour10Digit.handleMessage(sMessage);
            }
            else{
                throw std::invalid_argument("CapsuleRunner unable to deal with incMessage to capsule id: " + std::to_string(sMessage.toId));
            }
        }
        else{
            throw std::invalid_argument("CapsuleRunner unable to deal with that message");
        }
    }
}

Message CapsuleRunner::invokeMessage(Message request){
    if(std::holds_alternative<NoContentMessage>(request)){
        throw std::invalid_argument("CapsuleRunner cannot invoke emptyMessage");
    }
    else if(std::holds_alternative<RequestDigitMessage>(request)){
        RequestDigitMessage rMessage = std::get<RequestDigitMessage>(request);
        if(rMessage.toId == _second1Digit.getId()){
            return _second1Digit.handleInvokeMessage(rMessage);
        }
        else if(rMessage.toId == _second10Digit.getId()){
            return _second10Digit.handleInvokeMessage(rMessage);
        }
        else if(rMessage.toId == _minute1Digit.getId()){
            return _minute1Digit.handleInvokeMessage(rMessage);
        }
        else if(rMessage.toId == _minute10Digit.getId()){
            return _minute10Digit.handleInvokeMessage(rMessage);
        }
        else if(rMessage.toId == _hour1Digit.getId()){
            return _hour1Digit.handleInvokeMessage(rMessage);
        }
        else if(rMessage.toId == _hour10Digit.getId()){
            return _hour10Digit.handleInvokeMessage(rMessage);
        }
        else{
            throw std::invalid_argument("CapsuleRunner can't invoke RequestDigit with id: " + std::to_string(rMessage.toId));
        }
    }
    else{
        throw std::invalid_argument("CapsuleRunner received invokeMessage of wrong type");
    }
}