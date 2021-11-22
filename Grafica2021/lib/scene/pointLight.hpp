#pragma once

#include "../math/vec3.cpp"

#ifndef pointLight_HPP
#define pointLight_HPP

using namespace std;

class pointLight{
    public:
        vec3 origen;
        float potencia;
        pointLight();
        pointLight(vec3 Norigen, float Npotencia);
};

#endif