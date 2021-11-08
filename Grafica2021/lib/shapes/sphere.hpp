#pragma once

#include "../math/vec3.cpp"
#include "../scene/ray.cpp"
#include "colour.hpp"
#include "math.h"
#include "primitiva.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef sphere_HPP
#define sphere_HPP

class sphere : public Primitiva{
    public:
        vec3 center;
        float radius;
        colour color;
        sphere();
        sphere(vec3 center_, float radius_, colour color_);
        vec3 getCenter();
        float getRadius();
        bool ray_intersect(ray& r, colour& tono, float& distancia) const override;
        string queSoy() const override;
};

#endif