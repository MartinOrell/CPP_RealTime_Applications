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
        Client_Capsule _client;
        Server_Capsule _server;
        MessageHandler<Message>* _messageHandlerPtr;
        int _nextCapsuleId;
};