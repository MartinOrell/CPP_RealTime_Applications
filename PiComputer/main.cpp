#include "Message.h"
#include "MessageHandler.h"
#include "CapsuleRunner.h"
#include "PiComputer_Capsule.h"
#include "Adder_Capsule.h"
#include "Multiplier_Capsule.h"

int main(){
    MessageHandler<SendMessage> messageHandler;

    std::vector<std::unique_ptr<Capsule>> capsules;
    CapsuleRunner capsuleRunner(&messageHandler, &capsules);

    int nextCapsuleId = 0;

    std::unique_ptr<PiComputer_Capsule> piComputer = std::make_unique<PiComputer_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Adder_Capsule> adder = std::make_unique<Adder_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Multiplier_Capsule> multiplier = std::make_unique<Multiplier_Capsule>(nextCapsuleId++, &messageHandler);

    piComputer->connectAdder(adder->getId());
    adder->connectPiComputer(piComputer->getId());
    adder->connectMultiplier(multiplier->getId());
    multiplier->connectAdder(adder->getId());

    capsules.push_back(std::move(piComputer));
    capsules.push_back(std::move(adder));
    capsules.push_back(std::move(multiplier));

    capsuleRunner.run();
}