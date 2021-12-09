#pragma once

#include "../math/vec3.cpp"
#include "../scene/ray.cpp"
#include "../images/texture.cpp"
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
        virtual bool ray_intersect(ray rayo, colour& tono, float& distancia, vec3& normalParam) const = 0;
        virtual bool ray_intersect2(ray rayo, colour& tono, float& distancia, vec3& normalParam) const = 0;
        virtual string queSoy() const=0;
        virtual void material(float& Kd, float& Ks, float& Kr) const=0;
        virtual bool getEmisor() const=0;
        virtual float getRIndex() const=0;
        virtual bool getTextura(int x, int y, int tipo,  Pixel& pixelTextura) const=0;

};

#endif