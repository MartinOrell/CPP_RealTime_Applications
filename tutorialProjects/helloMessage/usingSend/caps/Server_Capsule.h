#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <stdexcept>

namespace mrt{
    class CapsuleRunner;
}

class Server_Capsule: public mrt::Capsule{
    public:
        Server_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);

        void connect(int clientId);
        
    private:
        void sendMessage(int toId, int value);

        void handleMessage(mrt::Request message);

        int _id;
        int _clientId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
};