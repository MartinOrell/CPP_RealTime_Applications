#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "Capsule.h"
#include "CapsuleRunner.h"
#include <vector>
#include <memory>
#include "HelloTimer_Capsule.h"

int main(){

    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++);
    auto helloTimer = std::make_unique<HelloTimer_Capsule>(nextCapsuleId++, &capsuleRunner);

    capsuleRunner.addCapsule(std::move(helloTimer));

    capsuleRunner.run();
}