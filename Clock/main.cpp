#include "MessageManager.h"
#include "CapsuleRunner.h"
#include <memory>
#include <thread>
#include "Main_Capsule.h"
#include "Clock_Capsule.h"
#include "Digit_Capsule.h"

int main(){
    
    std::chrono::steady_clock::duration timeoutTime = std::chrono::seconds(3600);
    int fps = 3;
    int speedMultiplier = 8;

    MessageManager messageManager;

    int nextCapsuleId = 0;

    CapsuleRunner capsuleRunner(nextCapsuleId++, &messageManager);
    CapsuleRunner timerRunner(nextCapsuleId++, &messageManager);
    auto main = std::make_unique<Main_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner, timeoutTime, fps);
    auto clock = std::make_unique<Clock_Capsule>(nextCapsuleId++, &capsuleRunner, &timerRunner, speedMultiplier);
    auto second1Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto second10Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto minute1Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto minute10Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto hour1Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &capsuleRunner);
    auto hour10Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &capsuleRunner);

    main->connect(clock->getId());
    clock->connectMain(main->getId());
    clock->connectSecond1Digit(second1Digit->getId());
    second1Digit->connect(clock->getId());
    clock->connectSecond10Digit(second10Digit->getId());
    second10Digit->connect(clock->getId());
    clock->connectMinute1Digit(minute1Digit->getId());
    minute1Digit->connect(clock->getId());
    clock->connectMinute10Digit(minute10Digit->getId());
    minute10Digit->connect(clock->getId());
    clock->connectHour1Digit(hour1Digit->getId());
    hour1Digit->connect(clock->getId());
    clock->connectHour10Digit(hour10Digit->getId());
    hour10Digit->connect(clock->getId());
    
    capsuleRunner.addCapsule(std::move(main));
    capsuleRunner.addCapsule(std::move(clock));
    capsuleRunner.addCapsule(std::move(second1Digit));
    capsuleRunner.addCapsule(std::move(second10Digit));
    capsuleRunner.addCapsule(std::move(minute1Digit));
    capsuleRunner.addCapsule(std::move(minute10Digit));
    capsuleRunner.addCapsule(std::move(hour1Digit));
    capsuleRunner.addCapsule(std::move(hour10Digit));
    
    std::jthread timerThread = std::jthread([&timerRunner](){timerRunner.run();});
    capsuleRunner.run();
    timerRunner.stop();
}