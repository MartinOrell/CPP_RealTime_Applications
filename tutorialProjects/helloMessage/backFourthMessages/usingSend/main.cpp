#include "Message.h"
#include "MessageHandler.h"
#include "CapsuleRunner.h"

int main(){
    MessageHandler<Message> messageHandler;
    CapsuleRunner capsuleRunner(&messageHandler);
    capsuleRunner.run();
}