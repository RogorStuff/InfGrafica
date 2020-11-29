#include "pixel.hpp"

#ifndef refelctance_HPP
#define refelctance_HPP

class Reflectance{
    public:
        Pixel kd;
        Pixel ks; 
        Pixel kdDiffuse;
        Pixel ksDiffuse;
        Reflectance();
        Reflectance(Pixel Nkd, Pixel Nks, Pixel NkdDiffuse, Pixel NksDiffuse);
};

#endif