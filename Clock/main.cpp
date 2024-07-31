#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "CapsuleRunner.h"

int main(){
    MessageHandler<SendMessage> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();
    std::chrono::steady_clock::duration timeoutTime = std::chrono::seconds(3600);
    int fps = 3;
    int speedMultiplier = 8;
    CapsuleRunner capsuleRunner(&timerThread, &messageHandler, timeoutTime, fps, speedMultiplier);
    capsuleRunner.run();
    timerThread.stop();
}