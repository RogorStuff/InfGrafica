#pragma once

#include "emission.hpp"

using namespace std;

Emission::Emission(){}

Emission::Emission(float Ered, float Egreen, float Eblue){
    red=Ered;
    green=Egreen;
    blue=Eblue;
}

void Emission::getEmision(float& Rred, float& Rgreen, float& Rblue){
    Rred=red;
    Rgreen=green;
    Rblue=blue;
}