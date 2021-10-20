#pragma once

#include "ray.hpp"

using namespace std;

ray::ray(){}

ray::ray(vec3 Norigen, vec3 Ndireccion){
    origen=Norigen;
    direccion=Ndireccion;
}
