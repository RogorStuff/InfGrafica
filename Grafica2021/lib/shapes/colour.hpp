#pragma once

#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef colour_HPP
#define colour_HPP

class colour {
    public:
        float R;
        float G;
        float B;
        colour();
        colour(float Rgb, float rGb, float rgB);
        void printColour();
};

#endif