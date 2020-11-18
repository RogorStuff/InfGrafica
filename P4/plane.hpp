#include "obstacle.hpp"
#include "emission.hpp"

#ifndef plane_HPP
#define plane_HPP

using namespace std;

class Plane: public Obstacle{//Todos los planos deben mirar hacia la cámara
    public:
        Emission emision;
        Vectores normal;
        Vectores center;
        Plane();
        Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision);
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia) const override;
    
};

#endif plane_HPP

