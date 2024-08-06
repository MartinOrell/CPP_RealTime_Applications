#pragma once

#include "Capsule.h"

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

class CapsuleRunner;

class Worker_Capsule: public Capsule{
    public:
        Worker_Capsule(int id);
        int getId();
        void start();
        
    private:
        int _id;
};