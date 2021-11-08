#pragma once

#include "../math/vec3.cpp"
#include "../scene/ray.cpp"
#include "colour.hpp"
#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include "primitiva.hpp"

using namespace std;

#ifndef sphere_HPP
#define sphere_HPP

class sphere : public Primitiva {
    public:
        vec3 center;
        float radius;
        colour color;
        float diffuse;
        float reflective;
        float refractive;
        float refractIndex;
        bool emisor;
        sphere();
        sphere(vec3 center_, float radius_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor);
        vec3 getCenter();
        float getRadius();
        float getDiffuse();
        float getReflective();
        float getRefractive();
        bool getEmisor();
        bool ray_intersect(ray& r, colour& tono, float& distancia,  vec3 normal) const override;
        string queSoy() const override;
        void material(float& Kd, float& Ks, float& Kr) const override;
        bool getEmisor() const override;
        float getRIndex() const override;
};

#endif