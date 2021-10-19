#pragma once

#include "../math/vec3.cpp"
#include "colour.hpp"
#include "math.h"
#include <vector>
#include <string> 
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef plane_HPP
#define plane_HPP

class plane {
    public:
        vec3 center;
        vec3 normal;
        colour color;
        plane();
        plane(vec3 center_,vec3 normal_, colour color_);
        vec3 getCenter();
        vec3 getNormal();
        void printCenter();
        void printNormal();
};

#endif