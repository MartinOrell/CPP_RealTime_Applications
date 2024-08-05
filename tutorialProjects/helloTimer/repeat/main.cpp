#include "Message.h"
#include "SendMessage.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "Capsule.h"
#include "CapsuleRunner.h"
#include <vector>
#include <memory>
#include "HelloTimer_Capsule.h"

int main(){
    MessageHandler<SendMessage> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();

    std::vector<std::unique_ptr<Capsule>> capsules;
    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageHandler, &capsules);
    std::unique_ptr<HelloTimer_Capsule> helloTimer = std::make_unique
        <HelloTimer_Capsule>(nextCapsuleId++, &messageHandler, &timerThread, &capsuleRunner);

    capsules.push_back(std::move(helloTimer));

    capsuleRunner.run();
    timerThread.stop();
}