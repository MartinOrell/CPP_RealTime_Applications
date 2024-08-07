#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include <stdexcept>

class Server_Capsule: public Capsule{
    public:
        Server_Capsule(int id);
        int getId();
        void start();
        Message handleInvokeMessage(Message message);
        
        void connect(int index, int clientId);

    private:
        Message handleInvokeMessage(Request inMessage);

        int _id;
        int _clientIds[3];
};