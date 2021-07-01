#pragma once

#include "sphere.hpp"

#ifndef plane_HPP
#define plane_HPP

using namespace std;

class Plane: public Obstacle{//Todos los planos deben mirar hacia la cámara
    public:
        Emission emision;
        Vectores normal;
        Vectores center;
        Material material;
        float refractiveIndex;
        Plane();
        Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision, Material Nmaterial, float NrefractiveIndex);
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia, Material& material, float &refractive) const override;
        Emission getColor() const override;
        string queSoy() const override;
        Vectores sacarVectorObjeto() const override;
};

#endif

