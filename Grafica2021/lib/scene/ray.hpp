#pragma once

#include "../math/vec3.cpp"

#ifndef ray_HPP
#define ray_HPP

using namespace std;

class ray{
    public:
        vec3 origen;
        vec3 direccion;
        ray();
        ray(vec3 Norigen, vec3 Ndireccion);
};

#endif