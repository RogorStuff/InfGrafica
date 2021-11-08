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


#ifndef obstacle_HPP
#define obstacle_HPP

using namespace std;

class Primitiva{
    public:
        virtual bool ray_intersect(ray& rayo, colour& tono, float& distancia) const = 0;
        virtual string queSoy() const=0;
};

#endif