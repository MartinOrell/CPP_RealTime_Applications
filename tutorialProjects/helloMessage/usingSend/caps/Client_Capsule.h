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
        int getId() override;
        void start() override;
        void receiveMessage(const mrt::Message& message) override;

        void connect(int serverId);
        
    private:
        void sendMessage(int toId, int value);

        void receiveMessage(const mrt::Response& message);

        int _id;
        int _serverId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{WaitForResponse, End};
        State _state;
};