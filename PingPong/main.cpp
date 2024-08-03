#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "CapsuleRunner.h"
#include "Ping_Capsule.h"
#include "Pong_Capsule.h"

int main(){
    MessageHandler<SendMessage> messageHandler;

    TimerThread timerThread(&messageHandler);
    timerThread.run();

    std::vector<std::unique_ptr<Capsule>> capsules;
    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageHandler, &capsules);
    std::unique_ptr<Ping_Capsule> pinger = std::make_unique
        <Ping_Capsule>(nextCapsuleId++, &messageHandler, &timerThread);
    std::unique_ptr<Pong_Capsule> ponger = std::make_unique
        <Pong_Capsule>(nextCapsuleId++, &messageHandler);

    pinger->connect(ponger->getId());
    ponger->connect(pinger->getId());

    capsules.push_back(std::move(pinger));
    capsules.push_back(std::move(ponger));

    capsuleRunner.run();
    timerThread.stop();
}