#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "HelloWorld_Capsule.h"

int main(){

    mrt::MessageManager messageManager;
    
    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    mrt::CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto hello = std::make_unique<HelloWorld_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner);

    capsuleRunner.addCapsule(std::move(hello));

    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    capsuleRunner.run();
    timerRunner.stop();
}