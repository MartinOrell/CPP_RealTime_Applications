#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "Ping_Capsule.h"
#include "Pong_Capsule.h"

int main(){

    mrt::MessageManager messageManager;

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    mrt::CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto pinger = std::make_unique<Ping_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner);
    auto ponger = std::make_unique<Pong_Capsule>(nextCapsuleId++, &capsuleRunner);

    pinger->connect(ponger->getId());
    ponger->connect(pinger->getId());

    capsuleRunner.addCapsule(std::move(pinger));
    capsuleRunner.addCapsule(std::move(ponger));

    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    capsuleRunner.run();
    timerRunner.stop();
}