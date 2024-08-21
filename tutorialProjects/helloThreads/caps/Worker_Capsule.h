#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

namespace mrt{
    class CapsuleRunner;
}

class Worker_Capsule: public mrt::Capsule{
    public:
        Worker_Capsule(int id);
        int getId();
        void start();
        
    private:
        int _id;
};