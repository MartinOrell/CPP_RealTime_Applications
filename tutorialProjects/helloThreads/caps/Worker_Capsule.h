#pragma once

#include "Capsule.h"

class Worker_Capsule: public mrt::Capsule{
    public:
        Worker_Capsule(int id);
        int getId() override;
        void start() override;
        
    private:
        int _id;
};