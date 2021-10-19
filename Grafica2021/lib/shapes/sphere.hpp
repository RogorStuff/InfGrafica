#pragma once

#include "../math/vec3.cpp"
#include "colour.hpp"
#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef sphere_HPP
#define sphere_HPP

class sphere {
    public:
        vec3 center;
        float radius;
        colour color;
        sphere();
        sphere(vec3 center_, float radius_, colour color_);
        vec3 getCenter();
        float getRadius();
};

#endif