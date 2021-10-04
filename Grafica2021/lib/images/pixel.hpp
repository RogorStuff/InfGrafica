#pragma once

#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef pixel_HPP
#define pixel_HPP

class Pixel {
    public:
        int R;
        int G;
        int B;
        Pixel();
        Pixel(int Rgb, int rGb, int rgB);
        Pixel GammaCurve(float gamma, int max, float m, int c);
};

#endif