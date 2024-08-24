#include "CapsuleRunner.h"
#include <memory>
#include "HelloTimer_Capsule.h"

int main(){
    
    auto updateTime = std::chrono::milliseconds(500);
    auto runDuration = std::chrono::seconds(3);

    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++);
    auto hello = std::make_unique<HelloTimer_Capsule>(nextCapsuleId++, &capsuleRunner, updateTime, runDuration);

    capsuleRunner.addCapsule(std::move(hello));

    capsuleRunner.run();
}