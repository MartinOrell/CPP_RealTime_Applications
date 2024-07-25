#include <iostream>
#include <chrono>
#include "TimerThread.h"
#include "MessageHandler.h"

int main(){
    MessageHandler<int> messageHandler;
    TimerThread timerThread(&messageHandler);
    timerThread.run();
    timerThread.informIn(std::chrono::milliseconds(500));
    timerThread.informIn(std::chrono::seconds(1));
    timerThread.informIn(std::chrono::seconds(2));
    timerThread.informIn(std::chrono::seconds(2));
    int endId = timerThread.informIn(std::chrono::seconds(3));
    
    while(true){
        while(messageHandler.hasMessage()){
            int message = messageHandler.popMessage();
            std::cout << "Timeout reached with id: " << message << std::endl;
            if(message == endId){
                goto end;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    end:
    std::cout << "End Reached" << std::endl;
}