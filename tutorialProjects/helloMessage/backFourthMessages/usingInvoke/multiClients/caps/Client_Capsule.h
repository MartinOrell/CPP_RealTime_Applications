#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class Client_Capsule: public Capsule{
    public:
        Client_Capsule(int id, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();

        void connect(int serverId);
    private:
        Response invokeRequest(int toId, int value);

        int _id;
        int _serverId;
        CapsuleRunner* _capsuleRunnerPtr;
};