#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include "Message.h"
#include <stdexcept>
#include <vector>

class Server_Capsule: public mrt::Capsule{
    public:
        Server_Capsule(int id, int numClients);
        int getId();
        void start();
        mrt::Message handleInvokeMessage(mrt::Message message);
        
        void connect(int index, int clientId);

    private:
        mrt::Message handleInvokeMessage(mrt::Request inMessage);

        int _id;
        std::vector<int> _clientIds;
};