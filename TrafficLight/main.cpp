#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "TrafficLight_Capsule.h"

int main(){

    mrt::MessageManager messageManager;

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    mrt::CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto trafficLight = std::make_unique<TrafficLight_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner);

    capsuleRunner.addCapsule(std::move(trafficLight));

    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    capsuleRunner.run();
    timerRunner.stop();
}