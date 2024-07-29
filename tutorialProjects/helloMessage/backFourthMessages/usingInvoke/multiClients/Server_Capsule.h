#pragma once

#include <string>
#include <iostream>
#include "Message.h"

class Server_Capsule{
    public:
        Server_Capsule(int id);
        int getId();
        void connect(int index, int clientId);
        void start();
        Message handleInvokeMessage(Request inMessage);
    private:
        int _id;
        int _clientIds[3];
};