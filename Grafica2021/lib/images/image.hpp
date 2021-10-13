#pragma once

#include "math.h"
#include "pixel.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef image_HPP
#define image_HPP

class Image {
    public:
        string formatID;
        float m;
        string name;
        int width, height;
        int c;
        int total;
        vector<Pixel> imageMatrix; //imageMatrix[height][width]
        Image();
        Image(string fileName, bool nueva, int Nwidth, int Nheight);
        
        void saveLDR(string newFileName);
        float getBiggerValueRGB();
};

#endif