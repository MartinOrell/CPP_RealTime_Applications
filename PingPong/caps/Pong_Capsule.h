#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"

class CapsuleRunner;

class Pong_Capsule: public Capsule{
    public:
        Pong_Capsule(int id, CapsuleRunner* capsuleRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connect(int pingId);
    private:
        void sendMessageToPing(int toId);

        void handleMessage(MessageToPong message);

        int _id;
        int _pingId;
        CapsuleRunner* _capsuleRunnerPtr;
};