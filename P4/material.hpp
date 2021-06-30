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
        Material Reflector();
        bool isEmissor();
};

#endif