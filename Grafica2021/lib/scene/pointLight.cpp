#pragma once

#include "pointLight.hpp"

using namespace std;

pointLight::pointLight(){}

pointLight::pointLight(vec3 Norigen, float Npotencia){
    origen=Norigen;
    potencia=Npotencia;
}
