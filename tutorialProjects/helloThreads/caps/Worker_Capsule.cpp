#include "Worker_Capsule.h"

Worker_Capsule::Worker_Capsule(int id){
    _id = id;
}

int Worker_Capsule::getId(){
    return _id;
}

void Worker_Capsule::start(){
    std::cout << "Worker[" + std::to_string(_id) + "]: Working for 3 seconds\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Worker[" + std::to_string(_id) + "]: Works done!\n";
}