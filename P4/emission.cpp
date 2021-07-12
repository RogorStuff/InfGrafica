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

Emission Emission::operator*(Emission e2) const{
    return Emission(red * e2.red, green * e2.green, blue * e2.blue);
}

Emission Emission::operator/(float e) const{
    return Emission(red / e, green / e, blue / e);
}