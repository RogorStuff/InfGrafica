#pragma once

#include "colour.hpp"

colour::colour(){
}

colour::colour(float Rgb, float rGb, float rgB){
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}
/* CANCER
string colour::printColour(){
    cout<<this->R<<" - "<<this->G<<" - "<<this->B;
}*/

void colour::printColour(){
    cout<<this->R<<" - "<<this->G<<" - "<<this->B;
}


ostream& operator<<(ostream& os, const colour& vec)
{
    os << "R: "<< vec.R << "| G: " << vec.G << "| B: " << vec.B;
    return os;
}