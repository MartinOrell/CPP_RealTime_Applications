#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Client_Capsule: public mrt::Capsule{
    public:
        Client_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();

        void connect(int serverId);
    private:
        mrt::Response invokeRequest(int toId, int value);

        int _id;
        int _serverId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
};