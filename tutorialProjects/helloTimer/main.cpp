#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "Capsule.h"
#include "CapsuleRunner.h"
#include <vector>
#include <memory>
#include "HelloTimer_Capsule.h"
#include <thread>
#include "MessageManager.h"

int main(){

    MessageManager messageManager;

    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto helloTimer = std::make_unique<HelloTimer_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner);

    capsuleRunner.addCapsule(std::move(helloTimer));

    std::jthread timerThread = std::jthread([&timerRunner](std::stop_token stop_token){
        timerRunner.run();
    });
    capsuleRunner.run();
    timerRunner.stop();
}