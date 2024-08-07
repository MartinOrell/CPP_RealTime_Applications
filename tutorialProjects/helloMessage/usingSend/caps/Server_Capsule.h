#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <stdexcept>

class CapsuleRunner;

class Server_Capsule: public Capsule{
    public:
        Server_Capsule(int id, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);

        void connect(int clientId);
        
    private:
        void sendMessage(int toId, int value);

        void handleMessage(Request message);

        int _id;
        int _clientId;
        CapsuleRunner* _capsuleRunnerPtr;
};