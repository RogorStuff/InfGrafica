#pragma once

#include "../math/vec3.cpp"
#include "../scene/ray.cpp"
#include "colour.hpp"
#include "math.h"
#include <vector>
#include <string> 
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include "primitiva.hpp"

using namespace std;

#ifndef plane_HPP
#define plane_HPP

class plane : public Primitiva {
    public:
        vec3 center;
        vec3 normal;
        colour color;
        float diffuse;
        float reflective;
        float refractive;
        float refractIndex;
        bool emisor;
        plane();
        plane(vec3 center_,vec3 normal_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor);
        vec3 getCenter();
        vec3 getNormal();
        float getDiffuse();
        float getReflective();
        float getRefractive();
        bool getEmisor();
        bool ray_intersect(ray& rayo, colour& tono, float& distancia, vec3& normalParam) const override;
        string queSoy() const override;
        void material(float& Kd, float& Ks, float& Kr) const override;
        bool getEmisor() const override;
        float getRIndex() const override;
};

#endif