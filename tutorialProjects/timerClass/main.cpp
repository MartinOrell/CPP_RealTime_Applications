#include <iostream>
#include <chrono>
#include "TimerThread.h"
#include "MessageHandler.h"

//ticks every 0.3 seconds until 3 seconds is reached
int main(){
    MessageHandler<int> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();
    int tickId = timerThread.informEvery(std::chrono::milliseconds(300));
    int endId = timerThread.informIn(std::chrono::seconds(3));

    while(true){
        messageHandler.waitForMessage();
        int message = messageHandler.popMessage();

        if(message == tickId){
            std::cout << "main: tick!" << std::endl;
        }
        if(message == endId){
            timerThread.cancelTimer(tickId);
            break;
        }
    }
    timerThread.stop();
    std::cout << "main: end reached\n";
}