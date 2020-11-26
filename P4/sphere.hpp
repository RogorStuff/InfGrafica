#include "obstacle.hpp"
#include "emission.hpp"

#ifndef sphere_HPP
#define sphere_HPP

using namespace std;

class Sphere: public Obstacle{
    public:
        float refractiveIndex;
        float radius;
        Emission emision;
        Vectores center;
        //Meter material
        Sphere();
        Sphere(Vectores Ncentro, float Nradio, Emission Nemision);
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia)const override;
};

#endif sphere_HPP

