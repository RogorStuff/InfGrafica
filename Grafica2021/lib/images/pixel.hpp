#pragma once

#include "../shapes2/colour.hpp"
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
        float R;
        float G;
        float B;
        Pixel();
        Pixel(float Rgb, float rGb, float rgB);
        void update(Pixel pixelNuevo);
        void update(colour pixelNuevo);
        Pixel GammaCurve(float gamma, int max, float m, int c);
};

#endif