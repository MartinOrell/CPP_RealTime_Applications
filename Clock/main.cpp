#include "lib/Message.h"
#include "lib/MessageHandler.h"
#include "lib/TimerThread.h"
#include "lib/CapsuleRunner.h"
#include "caps/Main_Capsule.h"
#include "caps/Clock_Capsule.h"
#include "caps/Digit_Capsule.h"
#include <vector>
#include <memory>

int main(){
    MessageHandler<SendMessage> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();

    std::vector<std::unique_ptr<Capsule>> capsules;
    CapsuleRunner capsuleRunner(&messageHandler, &capsules);

    int nextCapsuleId = 0;
    std::chrono::steady_clock::duration timeoutTime = std::chrono::seconds(3600);
    int fps = 3;
    int speedMultiplier = 8;

    std::unique_ptr<Main_Capsule> main = std::make_unique<Main_Capsule>(nextCapsuleId++, &messageHandler, &timerThread, timeoutTime, fps);
    std::unique_ptr<Clock_Capsule> clock = std::make_unique<Clock_Capsule>(nextCapsuleId++, &messageHandler, &timerThread, &capsuleRunner, speedMultiplier);
    std::unique_ptr<Digit_Capsule> second1Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Digit_Capsule> second10Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Digit_Capsule> minute1Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Digit_Capsule> minute10Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Digit_Capsule> hour1Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &messageHandler);
    std::unique_ptr<Digit_Capsule> hour10Digit = std::make_unique<Digit_Capsule>(nextCapsuleId++, &messageHandler);

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
    
    
    capsules.push_back(std::move(main));
    capsules.push_back(std::move(clock));
    capsules.push_back(std::move(second1Digit));
    capsules.push_back(std::move(second10Digit));
    capsules.push_back(std::move(minute1Digit));
    capsules.push_back(std::move(minute10Digit));
    capsules.push_back(std::move(hour1Digit));
    capsules.push_back(std::move(hour10Digit));
    capsuleRunner.run();
    timerThread.stop();
}