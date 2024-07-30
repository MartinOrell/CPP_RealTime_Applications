#pragma once

#include "Message.h"
#include "MessageHandler.h"

class Digit_Capsule{
    public:
        Digit_Capsule(int id, MessageHandler<Message>*messageHandlerPtr);
        int getId();
        void connect(int clockId);
        void start();
        void handleMessage(IncMessage inMessage);
        void handleMessage(SetBaseMessage inMessage);
        Message handleInvokeMessage(RequestDigitMessage inMessage);
    private:
        int _id;
        int _clockId;
        int _base;
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};
        State _state;
};