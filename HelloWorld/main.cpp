#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "CapsuleRunner.h"
#include "Capsule.h"
#include "HelloWorld_Capsule.h"

int main(){
    MessageHandler<SendMessage> messageHandler;
    
    TimerThread timerThread(&messageHandler);
    timerThread.run();

    std::vector<std::unique_ptr<Capsule>> capsules;
    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageHandler, &capsules);
    std::unique_ptr<HelloWorld_Capsule> hello = std::make_unique
        <HelloWorld_Capsule>(nextCapsuleId++, &messageHandler, &timerThread, &capsuleRunner);

    capsules.push_back(std::move(hello));

    capsuleRunner.run();
    timerThread.stop();
}