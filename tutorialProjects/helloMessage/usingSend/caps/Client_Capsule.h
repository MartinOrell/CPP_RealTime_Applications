#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <chrono>
#include <stdexcept>

namespace mrt{
    class CapsuleRunner;
}

class Client_Capsule: public mrt::Capsule{
    public:
        Client_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(mrt::Message message);

        void connect(int serverId);
        
    private:
        void sendMessage(int toId, int value);

        void handleMessage(mrt::Response message);

        int _id;
        int _serverId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{
            WaitForResponse, End
        };
        State _state;
};