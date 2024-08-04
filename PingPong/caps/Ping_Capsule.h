#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include "SendMessage.h"
#include <chrono>

class Ping_Capsule: public Capsule{
    public:
        Ping_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr, TimerThread* timerThreadPtr);
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
        TimerThread* _timerThreadPtr;
        MessageHandler<SendMessage>* _messageHandlerPtr;
};