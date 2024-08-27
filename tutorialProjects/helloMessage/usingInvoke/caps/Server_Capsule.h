#pragma once

#include "Capsule.h"

#include "Message.h"
#include <vector>

class Server_Capsule: public mrt::Capsule{
    public:
        Server_Capsule(int id, int numClients);
        int getId() override;
        void start() override;
        mrt::Message receiveInvokeMessage(const mrt::Message&) override;
        
        void connect(int index, int clientId);

    private:
        mrt::Message receiveInvokeMessage(const mrt::Request&);

        int _id;
        std::vector<int> _clientIds;
};