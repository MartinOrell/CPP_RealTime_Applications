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
        Message invokeMessage(Message request);
    private:
        int _nextCapsuleId;
        Server_Capsule _server;
        Client_Capsule _clients[3];
        
        MessageHandler<Message>* _messageHandlerPtr;
        
};