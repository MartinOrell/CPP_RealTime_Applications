#pragma once
#include <vector>
#include "CapsuleRunner.h"
#include "SendMessage.h"

class MessageManager{
    public:
        MessageManager();
        void addCapsuleRunnerPtr(CapsuleRunner* capsuleRunner);
        void sendMessage(SendMessage sendMessage);
        void mergeOrSendMessage(SendMessage);

    private:
        std::vector<CapsuleRunner*> _capsuleRunnerPtrs;
};