#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Client_Capsule.h"
#include "Server_Capsule.h"
#include "Message.h"

class CapsuleRunner{
    public:
        CapsuleRunner(MessageHandler<Message>*);
        void run();
    private:
        #define CLIENTID 0
        #define SERVERID 1
        Client_Capsule _client;
        Server_Capsule _server;
        MessageHandler<Message>* _messageHandlerPtr;
};