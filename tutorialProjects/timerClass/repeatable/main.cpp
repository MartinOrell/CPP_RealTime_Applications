#include <iostream>
#include <chrono>
#include "TimerThread.h"
#include "MessageHandler.h"

int main(){
    MessageHandler<int> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();
    int tickId = timerThread.informEvery(std::chrono::milliseconds(300));
    int endId = timerThread.informIn(std::chrono::seconds(3));
    
    while(true){
        while(messageHandler.hasMessage()){
            int message = messageHandler.popMessage();
            if(message == tickId){
                std::cout << "tick!" << std::endl;
            }
            if(message == endId){
                timerThread.cancelTimer(tickId);
                goto end;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    end:
    std::cout << "End Reached" << std::endl;
}