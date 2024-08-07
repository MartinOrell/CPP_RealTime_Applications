#pragma once

#include <string>
#include <iostream>
#include "Message.h"
#include "MessageHandler.h"

class Server_Capsule{
    public:
        Server_Capsule(int id, MessageHandler<Message>*messageHandlerPtr);
        int getId();
        void connect(int clientId);
        void start();
        void handleMessage(Request message);
    private:
        int _id;
        int _clientId;
        MessageHandler<Message>* _messageHandlerPtr;
};