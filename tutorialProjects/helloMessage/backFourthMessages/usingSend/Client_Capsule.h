#pragma once

#include <string>
#include <iostream>
#include "Message.h"
#include "MessageHandler.h"
#include <chrono>

class Client_Capsule{
    public:
        Client_Capsule(int id, MessageHandler<Message>* messageHandlerPtr);
        void connect(int serverId);
        void start();
        void handleMessage(Response message);
    private:
        int _id;
        int _serverId;
        MessageHandler<Message>* _messageHandlerPtr;
        enum State{
            WaitForResponse, End
        };
        State _state;
};