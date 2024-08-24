#include "CapsuleRunner.h"
#include <memory>
#include "HelloWorld_Capsule.h"

int main(){
    
    int nextCapsuleId = 0;

    mrt::CapsuleRunner capsuleRunner(nextCapsuleId++);
    auto hello = std::make_unique<HelloWorld_Capsule>(nextCapsuleId++, &capsuleRunner);

    capsuleRunner.addCapsule(std::move(hello));

    capsuleRunner.run();
}