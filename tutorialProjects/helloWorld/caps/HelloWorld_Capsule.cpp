#include "HelloWorld_Capsule.h"

#include "CapsuleRunner.h"

#include <iostream>

HelloWorld_Capsule::HelloWorld_Capsule(int id, mrt::CapsuleRunner* capsuleRunnerPtr)
: _id{id}
, _capsuleRunnerPtr{capsuleRunnerPtr}{}

int HelloWorld_Capsule::getId(){
    return _id;
}

void HelloWorld_Capsule::start(){
    std::cout << "Hello World!" << std::endl;
    _capsuleRunnerPtr->stop();
    _state = State::Hello;
}