#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Server_Capsule: public mrt::Capsule{
    public:
        Server_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId() override;
        void start() override;
        void handleMessage(const mrt::Message& message) override;

        void connect(int clientId);
        
    private:
        void sendMessage(int toId, int value);

        void handleMessage(const mrt::Request& message);

        int _id;
        int _clientId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
};