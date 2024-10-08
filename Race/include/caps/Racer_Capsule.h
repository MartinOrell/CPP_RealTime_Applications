#pragma once

#include "Capsule.h"

#include "Message.h"
#include "SendMessage.h"
#include <string>
#include "RacerProfile.h"

namespace mrt{
    class CapsuleRunner;
}

class Racer_Capsule: public mrt::Capsule{
    public:
        Racer_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr, mrt::CapsuleRunner* timerRunnerPtr, RacerProfile racerProfile, int goal);
        int getId() override;
        std::string getName();
        std::string getArtFilename();
        void receiveMessage(const mrt::Message&) override;
        void start() override;

        void connectMain(int mainId);
        void connectUI(int uiId);
    private:
        void sendDistanceResponse(int toId);
        void sendGoalReached(int toId);

        void handleTimeout(const mrt::TimeoutMessage&);
        void handleStartSignal();
        void handleStopSignal();
        void handleDistanceRequest();
        void handleWaitTimerTimeout(int timeouts);
        void handleStepTimerTimeout(int timeouts);

        void hearStartSignal();
        void startRunning();
        void step(int timeouts);
        void stop();

        int _id;
        int _mainId;
        int _uiId;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        mrt::CapsuleRunner* _timerRunnerPtr;
        RacerProfile _profile;
        int _waitTimerId;
        int _stepTimerId;
        std::chrono::steady_clock::duration _stepTime;
        int _numSteps;
        int _stamina;
        int _goal;
        enum State{WaitForStartSignal, ReactToStartSignal, Running, Resting};
        State _state;
};