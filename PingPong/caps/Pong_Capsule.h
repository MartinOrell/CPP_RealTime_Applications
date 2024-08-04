#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "TimerThread.h"
#include "Message.h"
#include "SendMessage.h"

class Pong_Capsule: public Capsule{
    public:
        Pong_Capsule(int id, MessageHandler<SendMessage>*messageHandlerPtr);
        int getId();
        void start();
        void handleMessage(Message message);
        
        void connect(int pingId);
    private:
        void sendMessageToPing(int toId);

        void handleMessage(MessageToPong message);

        int _id;
        int _pingId;
        MessageHandler<SendMessage>* _messageHandlerPtr;
};