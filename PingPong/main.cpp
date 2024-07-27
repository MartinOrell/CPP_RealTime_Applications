#include <iostream>
#include "Message.h"
#include "MessageHandler.h"
#include "TimerThread.h"
#include "CapsuleController.h"

int main(){
    MessageHandler<Message> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();
    CapsuleController capsuleController(&timerThread, &messageHandler);
    capsuleController.run();
    
    std::cout << "main: end reached\n";
}