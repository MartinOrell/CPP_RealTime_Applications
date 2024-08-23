#pragma once

#include "Capsule.h"

#include "Message.h"
#include <vector>

class Server_Capsule: public mrt::Capsule{
    public:
        Server_Capsule(int id, int numClients);
        int getId();
        void start();
        mrt::Message handleInvokeMessage(const mrt::Message& message);
        
        void connect(int index, int clientId);

    private:
        mrt::Message handleInvokeMessage(const mrt::Request& inMessage);

        int _id;
        std::vector<int> _clientIds;
};