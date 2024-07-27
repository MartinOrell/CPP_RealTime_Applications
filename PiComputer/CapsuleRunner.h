#pragma once

#include <variant>
#include "MessageHandler.h"
#include "Message.h"
#include "PiComputer_Capsule.h"
#include "Adder_Capsule.h"
#include "Multiplier_Capsule.h"

class CapsuleRunner{
    public:
        CapsuleRunner(MessageHandler<Message>*);
        void run();
    private:
        PiComputer_Capsule _piComputer;
        Adder_Capsule _adder;
        Multiplier_Capsule _multiplier;
        MessageHandler<Message>* _messageHandlerPtr;
};