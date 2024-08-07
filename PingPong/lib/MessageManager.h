#pragma once
#include <vector>
#include "CapsuleRunner.h"
#include "SendMessage.h"

class MessageManager{
    public:
        MessageManager(bool allowCrossInvoke = false);
        void addCapsuleRunnerPtr(CapsuleRunner* capsuleRunner);
        void sendMessage(SendMessage sendMessage);
        void mergeOrSendMessage(SendMessage);
        Message invokeMessage(SendMessage);

    private:
        bool _allowCrossInvoke;
        std::vector<CapsuleRunner*> _capsuleRunnerPtrs;
};