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
    CapsuleRunner capsuleRunner(&messageHandler, &capsules);

    int nextCapsuleId = 0;
    capsules.push_back(std::make_unique<HelloWorld_Capsule>(nextCapsuleId, &messageHandler, &timerThread));

    capsuleRunner.run();
    timerThread.stop();
}