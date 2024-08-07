#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class Client_Capsule: public Capsule{
    public:
        Client_Capsule(int id, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);

        void connect(int serverId);
        
    private:
        void sendMessage(int toId, int value);

        void handleMessage(Response message);

        int _id;
        int _serverId;
        CapsuleRunner* _capsuleRunnerPtr;
        enum State{
            WaitForResponse, End
        };
        State _state;
};