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
        float refractiveIndex;
        Sphere();
        Sphere(Vectores Ncentro, float Nradio, Emission Nemision, Material material, float NrefractiveIndex);
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia, Material& material, float &refractive)const override;
        Emission getColor()const override;
        string queSoy() const override;
        Vectores sacarVectorObjeto() const override;
};

#endif

