#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "Main_Capsule.h"
#include "Racer_Capsule.h"
#include "RacerProfile.h"

int main(){

    int numRacers = 2;
    int fps = 3;
    int goal = 100;

    RacerProfile tortoiseP;
    tortoiseP.name = "The Tortoise";
    tortoiseP.asciiFilename = "racerAscii/tortoise.txt";
    tortoiseP.speed = 15;
    tortoiseP.stamina = 100;
    tortoiseP.reactionTime = std::chrono::milliseconds(600);
    tortoiseP.restTime = std::chrono::seconds(1);

    RacerProfile hareP;
    hareP.name = "The Hare";
    hareP.asciiFilename = "racerAscii/hare.txt";
    hareP.speed = 20;
    hareP.stamina = 60;
    hareP.reactionTime = std::chrono::milliseconds(100);
    hareP.restTime = std::chrono::milliseconds(2200);

    MessageManager messageManager;

    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto main = std::make_unique<Main_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner, fps, goal);
    auto tortoise = std::make_unique<Racer_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner, tortoiseP, goal);
    auto hare = std::make_unique<Racer_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner, hareP, goal);

    main->connectRacer(tortoise->getId(), tortoise->getName(), tortoise->getAsciiFilename());
    tortoise->connect(main->getId());
    main->connectRacer(hare->getId(), hare->getName(), hare->getAsciiFilename());
    hare->connect(main->getId());

    capsuleRunner.addCapsule(std::move(main));
    capsuleRunner.addCapsule(std::move(tortoise));
    capsuleRunner.addCapsule(std::move(hare));

    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    capsuleRunner.run();
    timerRunner.stop();
}