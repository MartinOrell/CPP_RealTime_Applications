#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include <vector>
#include "HelloTimer_Capsule.h"

int main(){

    mrt::MessageManager messageManager;

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    mrt::CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto helloTimer = std::make_unique<HelloTimer_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner);

    capsuleRunner.addCapsule(std::move(helloTimer));

    std::jthread timerThread = std::jthread([&timerRunner](std::stop_token stop_token){
        timerRunner.run();
    });
    capsuleRunner.run();
    timerRunner.stop();
}