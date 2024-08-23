#pragma once

#include "Capsule.h"

class Worker_Capsule: public mrt::Capsule{
    public:
        Worker_Capsule(int id);
        int getId();
        void start();
        
    private:
        int _id;
};