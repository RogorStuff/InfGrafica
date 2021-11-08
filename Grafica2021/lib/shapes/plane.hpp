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

class plane : public Primitiva{
    public:
        vec3 center;
        vec3 normal;
        colour color;
        plane();
        plane(vec3 center_,vec3 normal_, colour color_);
        vec3 getCenter();
        vec3 getNormal();
        bool ray_intersect(ray& rayo, colour& tono, float& distancia) const override;
        string queSoy() const override;
};

#endif