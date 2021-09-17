#include "pixel.hpp"

#ifndef refelctance_HPP
#define refelctance_HPP

class Reflectance{
    public:
        float kd;
        float ks; 
        float kdDiffuse;
        float ksDiffuse;
        Reflectance();
        Reflectance(float Nkd, float Nks, float NkdDiffuse, float NksDiffuse);
};

#endif