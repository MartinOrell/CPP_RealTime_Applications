#pragma once

#include "Capsule.h"

namespace mrt{
    class CapsuleRunner;
}

class HelloWorld_Capsule: public mrt::Capsule{
    public:
        HelloWorld_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr);
        int getId() override;
        void start() override;
        
    private:

        int _id;
        mrt::CapsuleRunner* _capsuleRunnerPtr;
        enum State{Hello};
        State _state;
};