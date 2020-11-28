#include "pixel.hpp"

#ifndef refelctance_HPP
#define refelctance_HPP

class Reflectance{
    public:
        Pixel kd; // Refraction (delta BTDF)
        Pixel ks; // Specular (delta BRDF)
        Pixel kdPhong; //Phong BRDF
        Pixel ksPhong; // Phong BRDF
        float s; // Shininess
        Reflectance();
        Reflectance(Pixel Nkd, Pixel Nks, Pixel NkdPhong, Pixel NksPhong, float Ns);
};

#endif