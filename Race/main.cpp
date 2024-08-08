#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include <vector>
#include "Main_Capsule.h"
#include "Racer_Capsule.h"
#include "RacerProfile.h"

int main(){

    int numRacers = 2;
    int numRacerThreads = 2;
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

    CapsuleRunner mainCapsuleRunner(nextCapsuleId++, &messageManager);

    std::vector<CapsuleRunner> racerCapsuleRunners;
    for(int i = 0; i < numRacerThreads; i++){
        racerCapsuleRunners.push_back(CapsuleRunner(nextCapsuleId++, &messageManager));
    }
    CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto main = std::make_unique<Main_Capsule>(nextCapsuleId++, &mainCapsuleRunner, &timerRunner, fps, goal);
    auto tortoise = std::make_unique<Racer_Capsule>(nextCapsuleId++, &racerCapsuleRunners.at(0), &timerRunner, tortoiseP, goal);
    auto hare = std::make_unique<Racer_Capsule>(nextCapsuleId++, &racerCapsuleRunners.at(1), &timerRunner, hareP, goal);

    main->connectRacer(tortoise->getId(), tortoise->getName(), tortoise->getAsciiFilename());
    tortoise->connect(main->getId());
    main->connectRacer(hare->getId(), hare->getName(), hare->getAsciiFilename());
    hare->connect(main->getId());

    mainCapsuleRunner.addCapsule(std::move(main));
    racerCapsuleRunners.at(0).addCapsule(std::move(tortoise));
    racerCapsuleRunners.at(1).addCapsule(std::move(hare));

    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    std::jthread tortoiseThread = std::jthread([&runner = racerCapsuleRunners.at(0)](){runner.run();});
    std::jthread hareThread = std::jthread([&runner = racerCapsuleRunners.at(1)](){runner.run();});
    mainCapsuleRunner.run();
    racerCapsuleRunners.at(0).stop();
    racerCapsuleRunners.at(1).stop();
    timerRunner.stop();
}