#include "pixel.cpp"
#include <vector>
#include <string> 

using namespace std;

#ifndef image_HPP
#define image_HPP

class tspMatrix {
    public:
        string formatID;
        string name;
        float m;
        int c;
        int width, height;
        int total;
        vector<Pixel> imageMatrix; //imageMatrix[height][width]
        
        tspMatrix();
        tspMatrix(string fileName, bool nueva, int Nwidth, int Nheight);
        void save(string newFileName);
};

#endif