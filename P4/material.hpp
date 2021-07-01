#pragma once

#include "pixel.hpp"

#ifndef material_HPP
#define material_HPP

class Material{
    public:
        bool emisor;
        Material();
        Material Emitter();
        Material Reflector();
        bool isEmissor();
};

#endif