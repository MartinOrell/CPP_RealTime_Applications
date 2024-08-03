#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "CapsuleRunner.h"
#include "TrafficLight_Capsule.h"

int main(){
    MessageHandler<SendMessage> messageHandler;

    TimerThread timerThread(&messageHandler);
    timerThread.run();

    std::vector<std::unique_ptr<Capsule>> capsules;
    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageHandler, &capsules);
    std::unique_ptr<TrafficLight_Capsule> trafficLight = std::make_unique
        <TrafficLight_Capsule>(nextCapsuleId++, &messageHandler, &timerThread);

    capsules.push_back(std::move(trafficLight));

    capsuleRunner.run();
    timerThread.stop();
}