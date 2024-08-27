#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"

namespace mrt{
    class CapsuleRunner;
}

class Ping_Capsule: public mrt::Capsule{
    public:
        Ping_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr);
        int getId() override;
        void start() override;
        void receiveMessage(const mrt::Message&) override;
        
        void connect(int pongId);
    private:
        void sendMessageToPong(int toId, int count);

        void handleMessageToPing();
        void handleTimeout(const mrt::TimeoutMessage&);

        int _id;
        int _pongId;
        int _count;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
};