#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "Main_Capsule.h"
#include "Worker_Capsule.h"

int main(){

    MessageManager messageManager;

    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner1(nextCapsuleId++, &messageManager);
    CapsuleRunner capsuleRunner2(nextCapsuleId++, &messageManager);
    CapsuleRunner capsuleRunner3(nextCapsuleId++, &messageManager);
    CapsuleRunner capsuleRunner4(nextCapsuleId++, &messageManager);
    CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto main = std::make_unique<Main_Capsule>(nextCapsuleId++, &capsuleRunner1, &timerRunner);
    auto worker1 = std::make_unique<Worker_Capsule>(nextCapsuleId++);
    auto worker2 = std::make_unique<Worker_Capsule>(nextCapsuleId++);
    auto worker3 = std::make_unique<Worker_Capsule>(nextCapsuleId++);
    
    capsuleRunner1.addCapsule(std::move(main));
    capsuleRunner2.addCapsule(std::move(worker1));
    capsuleRunner3.addCapsule(std::move(worker2));
    capsuleRunner4.addCapsule(std::move(worker3));
    
    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    std::jthread worker1Thread = std::jthread([&capsuleRunner2](){capsuleRunner2.run();});
    std::jthread worker2Thread = std::jthread([&capsuleRunner3](){capsuleRunner3.run();});
    std::jthread worker3Thread = std::jthread([&capsuleRunner4](){capsuleRunner4.run();});
    capsuleRunner1.run();
    timerRunner.stop();
    capsuleRunner2.stop();
    capsuleRunner3.stop();
    capsuleRunner4.stop();
}