#include <vector>
#include "vector.cpp"

#ifndef ray_HPP
#define ray_HPP

using namespace std;

class Ray{
    public:
        Vectores origen;
        Vectores direccion;
        Ray();
        Ray(Vectores Norigen, Vectores Ndireccion);
};

#endif