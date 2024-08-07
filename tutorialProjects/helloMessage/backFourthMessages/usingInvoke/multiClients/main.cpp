#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "Server_Capsule.h"
#include "Client_Capsule.h"

int main(){

    int numClients = 3;

    MessageManager messageManager;

    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    auto server = std::make_unique<Server_Capsule>(nextCapsuleId++);

    for(int i = 0; i < numClients; i++){
        auto client = std::make_unique<Client_Capsule>(nextCapsuleId++, &capsuleRunner);
        server->connect(i, client->getId());
        client->connect(server->getId());
        capsuleRunner.addCapsule(std::move(client));
    }
    capsuleRunner.addCapsule(std::move(server));

    capsuleRunner.run();
}