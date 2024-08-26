#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "HelloTimer_Capsule.h"

int main(){

    mrt::MessageManager messageManager;

    auto updateTime = std::chrono::milliseconds(500);
    auto runDuration = std::chrono::seconds(3);

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    mrt::CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto helloTimer = std::make_unique<HelloTimer_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner, updateTime, runDuration);

    capsuleRunner.addCapsule(std::move(helloTimer));

    std::jthread timerThread = std::jthread([&timerRunner](){
        timerRunner.run();
    });
    capsuleRunner.run();
    timerRunner.stop();
}