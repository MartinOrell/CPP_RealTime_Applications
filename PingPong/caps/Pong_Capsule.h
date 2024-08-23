#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Pong_Capsule: public mrt::Capsule{
    public:
        Pong_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(const mrt::Message& message);
        
        void connect(int pingId);
    private:
        void sendMessageToPing(int toId);

        void handleMessage(const mrt::MessageToPong& message);

        int _id;
        int _pingId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
};