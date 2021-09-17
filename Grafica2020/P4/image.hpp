#pragma once

#include "pixel.cpp"
#include <string>
#include <vector>

using namespace std;


#ifndef image_HPP
#define image_HPP

class image {
    public:
        string formatID;
        string name;
        float m;
        int c;
        int width, height;
        int total;
        vector<Pixel> imageMatrix; //imageMatrix[height][width]
        
        image();
        image(string fileName, bool nueva, int Nwidth, int Nheight);
        void save(string newFileName);
};

#endif