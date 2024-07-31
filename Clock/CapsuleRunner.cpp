#include "CapsuleRunner.h"

CapsuleRunner::CapsuleRunner(TimerThread* timerThreadPtr, MessageHandler<SendMessage>* messageHandlerPtr, std::chrono::steady_clock::duration timeoutTime, int fps, int speedMultiplier)
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
        SendMessage sendMessage = _messageHandlerPtr->receiveMessage();
        if(sendMessage.toId == -1){
            Message message = sendMessage.message;
            if(std::holds_alternative<VoidMessage>(message)){
                VoidMessage voidMessage = std::get<VoidMessage>(message);
                if(voidMessage == VoidMessage::EndMessage){
                    return;
                }
                else{
                    throw std::invalid_argument("CapsuleRunner received emptyMessage of wrong type");
                }
            }
            else{
                throw std::invalid_argument("CapsuleRunner received message of wrong type");
            }
        }
        else if(sendMessage.toId == _main.getId()){
            _main.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _clock.getId()){
            _clock.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _second1Digit.getId()){
            _second1Digit.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _second10Digit.getId()){
            _second10Digit.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _minute1Digit.getId()){
            _minute1Digit.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _minute10Digit.getId()){
            _minute10Digit.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _hour1Digit.getId()){
            _hour1Digit.handleMessage(sendMessage.message);
        }
        else if(sendMessage.toId == _hour10Digit.getId()){
            _hour10Digit.handleMessage(sendMessage.message);
        }
        else{
            throw std::invalid_argument("CapsuleRunner unable to send handleMessage to capsule with id: " + std::to_string(sendMessage.toId));
        }
    }
}

Message CapsuleRunner::invokeMessage(SendMessage request){
    if(request.toId == _main.getId()){
        return _main.handleInvokeMessage(request.message);
    }
    else if(request.toId == _clock.getId()){
        return _clock.handleInvokeMessage(request.message);
    }
    else if(request.toId == _second1Digit.getId()){
        return _second1Digit.handleInvokeMessage(request.message);
    }
    else if(request.toId == _second10Digit.getId()){
        return _second10Digit.handleInvokeMessage(request.message);
    }
    else if(request.toId == _minute1Digit.getId()){
        return _minute1Digit.handleInvokeMessage(request.message);
    }
    else if(request.toId == _minute10Digit.getId()){
        return _minute10Digit.handleInvokeMessage(request.message);
    }
    else if(request.toId == _hour1Digit.getId()){
        return _hour1Digit.handleInvokeMessage(request.message);
    }
    else if(request.toId == _hour10Digit.getId()){
        return _hour10Digit.handleInvokeMessage(request.message);
    }
    else{
        throw std::invalid_argument("CapsuleRunner can't invokeMessage to capsule with id: " + std::to_string(request.toId));
    }
}