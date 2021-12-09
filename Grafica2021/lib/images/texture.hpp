#pragma once

#include "../shapes2/colour.hpp"
#include "pixel.cpp"
#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <fstream>
#include <iostream>

using namespace std;

#ifndef texture_HPP
#define texture_HPP

class Texture {
    public:
        vector<Pixel> contenido;
        float width;
        float height;
        float max;
        Texture();
        Texture(string fileName);
        Pixel getPixel(int x_, int y_);
};

#endif