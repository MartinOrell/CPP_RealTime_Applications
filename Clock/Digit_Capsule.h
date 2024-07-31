#pragma once

#include "Capsule.h"

#include "Message.h"
#include "MessageHandler.h"
#include <stdexcept>

class Digit_Capsule: public Capsule{
    public:
        Digit_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        Message handleInvokeMessage(Message request);

        void connect(int clockId);
        
    private:
        void handleMessage(IncMessage inMessage);
        void handleMessage(SetBaseMessage inMessage);
        Message handleInvokeMessage(RequestDigitMessage inMessage);

        int _id;
        int _clockId;
        int _base;
        MessageHandler<SendMessage>* _messageHandlerPtr;
        enum State{Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};
        State _state;
};