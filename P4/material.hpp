#pragma once

#include "pixel.hpp"

#ifndef material_HPP
#define material_HPP

class Material{
    public:
        bool emisor;

        float kd;
        float ks;
        float krefraction;

        Material();
        Material(float kd_, float ks_, float kref_);


        Material Emitter();
        Material Reflector();
        bool isEmissor();
};

#endif