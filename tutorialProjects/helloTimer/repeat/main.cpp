#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "Capsule.h"
#include "CapsuleRunner.h"
#include <vector>
#include <memory>
#include "HelloTimer_Capsule.h"

int main(){

    std::vector<std::unique_ptr<Capsule>> capsules;
    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &capsules);
    std::unique_ptr<HelloTimer_Capsule> helloTimer = std::make_unique
        <HelloTimer_Capsule>(nextCapsuleId++, &capsuleRunner);

    capsules.push_back(std::move(helloTimer));

    capsuleRunner.run();
}