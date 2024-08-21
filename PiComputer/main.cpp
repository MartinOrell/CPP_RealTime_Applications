#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "PiComputer_Capsule.h"
#include "Adder_Capsule.h"
#include "Multiplier_Capsule.h"

int main(){

    mrt::MessageManager messageManager;

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    auto piComputer = std::make_unique<PiComputer_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto adder = std::make_unique<Adder_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto multiplier = std::make_unique<Multiplier_Capsule>(nextCapsuleId++, &capsuleRunner);

    piComputer->connectAdder(adder->getId());
    adder->connectPiComputer(piComputer->getId());
    adder->connectMultiplier(multiplier->getId());
    multiplier->connectAdder(adder->getId());

    capsuleRunner.addCapsule(std::move(piComputer));
    capsuleRunner.addCapsule(std::move(adder));
    capsuleRunner.addCapsule(std::move(multiplier));

    capsuleRunner.run();
}