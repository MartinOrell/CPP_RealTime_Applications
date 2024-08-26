#include "CapsuleRunner.h"
#include <memory>
#include "Server_Capsule.h"
#include "Client_Capsule.h"

int main(){

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner{nextCapsuleId++};
    auto server = std::make_unique<Server_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto client = std::make_unique<Client_Capsule>(nextCapsuleId++, &capsuleRunner);

    server->connect(client->getId());
    client->connect(server->getId());

    capsuleRunner.addCapsule(std::move(server));
    capsuleRunner.addCapsule(std::move(client));

    capsuleRunner.run();
}