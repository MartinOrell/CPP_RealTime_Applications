#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "Server_Capsule.h"
#include "Client_Capsule.h"

int main(){

    int numClients = 3;

    mrt::MessageManager messageManager(true);

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    mrt::CapsuleRunner capsuleRunner2(nextCapsuleId++, &messageManager);
    auto server = std::make_unique<Server_Capsule>(nextCapsuleId++, numClients);

    for(int i = 0; i < numClients; i++){
        auto client = std::make_unique<Client_Capsule>(nextCapsuleId++, &capsuleRunner);
        server->connect(i, client->getId());
        client->connect(server->getId());
        capsuleRunner.addCapsule(std::move(client));
    }
    capsuleRunner2.addCapsule(std::move(server));

    std::jthread timerThread = std::jthread([&capsuleRunner2](){capsuleRunner2.run();});
    capsuleRunner.run();
    capsuleRunner2.stop();
}