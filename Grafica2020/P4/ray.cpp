#pragma once

#include "ray.hpp"

using namespace std;

Ray::Ray(){}

Ray::Ray(Vectores Norigen, Vectores Ndireccion){
    origen=Norigen;
    direccion=Ndireccion;
}
