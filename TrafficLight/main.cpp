#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "CapsuleRunner.h"

int main(){
    MessageHandler<Message> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();
    CapsuleRunner capsuleRunner(&timerThread, &messageHandler);
    capsuleRunner.run();
    timerThread.stop();
}