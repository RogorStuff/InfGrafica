#include "reflectance.hpp"
#include "pixel.hpp"

#ifndef material_HPP
#define material_HPP

class Material{
    public:
        bool emisor;
        Reflectance reflectance;
        Material();
        Material Emitter();
        Material Reflector(float kd, float ks, float kdDiffuse, float ksDiffuse);
        bool isEmissor();/*
        Material Phong(Pixel kdDiffuse, Pixel ksDiffuse);
        Material Diffuse(Pixel k);
        Material Delta(Pixel kd, Pixel ks);
        Material Refractor(Pixel kd);
        Material Specular(Pixel ks);*/
};

#endif