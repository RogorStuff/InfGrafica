#pragma once

#include <vector>
#include "ray.hpp"
#include "emission.hpp"
#include "material.hpp"

#ifndef obstacle_HPP
#define obstacle_HPP

using namespace std;

class Obstacle{
    public:
        virtual bool ray_intersect(Ray& rayo, Emission& emite, float& distancia, Material& material, Vectores &normalGolpe) const = 0;
        virtual Emission getColor() const=0;
        virtual string queSoy() const=0;
        virtual Vectores sacarVectorObjeto() const=0;
        virtual float getRefractiveIndex() const=0;
        virtual Material getMaterial() const = 0; 
};

#endif