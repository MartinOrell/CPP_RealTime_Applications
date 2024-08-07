#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include "SendMessage.h"
#include <chrono>
#include <stdexcept>

class CapsuleRunner;

class Ping_Capsule: public Capsule{
    public:
        Ping_Capsule(int id, CapsuleRunner* capsuleRunnerPtr, CapsuleRunner* timerRunnerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connect(int pongId);
    private:
        void sendMessageToPong(int toId, int count);

        void handleMessageToPing();
        void handleTimeout(TimeoutMessage message);

        int _id;
        int _pongId;
        int _count;
        CapsuleRunner* _capsuleRunnerPtr;
        CapsuleRunner* _timerRunnerPtr;
};