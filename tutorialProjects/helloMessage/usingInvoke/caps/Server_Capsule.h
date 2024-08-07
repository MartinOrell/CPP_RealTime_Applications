#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include <stdexcept>
#include <vector>

class Server_Capsule: public Capsule{
    public:
        Server_Capsule(int id, int numClients);
        int getId();
        void start();
        Message handleInvokeMessage(Message message);
        
        void connect(int index, int clientId);

    private:
        Message handleInvokeMessage(Request inMessage);

        int _id;
        std::vector<int> _clientIds;
};