#include "obstacle.hpp"
#include "emission.hpp"
#include "material.hpp"

#ifndef sphere_HPP
#define sphere_HPP

using namespace std;

class Sphere: public Obstacle{
    public:
        float radius;
        Emission emision;
        Vectores center;
        Material material;
        Sphere();
        Sphere(Vectores Ncentro, float Nradio, Emission Nemision, Material material);
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia, Material& material)const override;
};

#endif sphere_HPP

