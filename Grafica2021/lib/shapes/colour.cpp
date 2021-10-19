#pragma once

#include "colour.hpp"

colour::colour(){
}

colour::colour(float Rgb, float rGb, float rgB){
                cout<<Rgb << rGb<<rgB<<endl;
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}

string colour::printColour(){
    cout<<this->R<<" - "<<this->G<<" - "<<this->B;
}