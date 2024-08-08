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

    std::vector<RacerProfile> profiles;
    profiles.push_back(tortoiseP);
    profiles.push_back(hareP);

    MessageManager messageManager;

    int nextCapsuleId = 0;

    CapsuleRunner mainCapsuleRunner(nextCapsuleId++, &messageManager);

    std::vector<CapsuleRunner> racerCapsuleRunners;
    for(int i = 0; i < numRacerThreads; i++){
        racerCapsuleRunners.push_back(CapsuleRunner(nextCapsuleId++, &messageManager));
    }
    CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto main = std::make_unique<Main_Capsule>(nextCapsuleId++, &mainCapsuleRunner, &timerRunner, fps, goal);
    for(int i = 0; i < numRacers; i++){
        auto racer = std::make_unique<Racer_Capsule>(nextCapsuleId++, &racerCapsuleRunners.at(i%numRacerThreads), &timerRunner, profiles.at(i%profiles.size()), goal);
        main->connectRacer(racer->getId(), racer->getName(), racer->getAsciiFilename());
        racer->connect(main->getId());
        racerCapsuleRunners.at(i%racerCapsuleRunners.size()).addCapsule(std::move(racer));
    }

    mainCapsuleRunner.addCapsule(std::move(main));

    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    std::vector<std::jthread> racerThreads;
    for(int i = 0; i < racerCapsuleRunners.size(); i++){
        racerThreads.push_back(std::jthread([&runner = racerCapsuleRunners.at(i)](){runner.run();}));
    }
    mainCapsuleRunner.run();
    for(int i = 0; i < racerCapsuleRunners.size(); i++){
        racerCapsuleRunners.at(i).stop();
    }
    timerRunner.stop();
}