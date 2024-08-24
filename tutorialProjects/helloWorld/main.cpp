#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include "HelloWorld_Capsule.h"

int main(){

    mrt::MessageManager messageManager;
    
    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    auto hello = std::make_unique<HelloWorld_Capsule>(nextCapsuleId++, &capsuleRunner);

    capsuleRunner.addCapsule(std::move(hello));

    capsuleRunner.run();
}