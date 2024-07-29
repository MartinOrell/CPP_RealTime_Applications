#pragma once

#include <string>
#include <iostream>
#include "Message.h"
#include "MessageHandler.h"
#include <chrono>

class CapsuleRunner;

class Client_Capsule{
    public:
        Client_Capsule(int id, MessageHandler<Message>* messageHandlerPtr, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void connect(int serverId);
        void start();
    private:
        int _id;
        int _serverId;
        MessageHandler<Message>* _messageHandlerPtr;
        CapsuleRunner* _capsuleRunnerPtr;
};