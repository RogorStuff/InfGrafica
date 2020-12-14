#include "reflectance.hpp"

Reflectance::Reflectance(){
}

Reflectance::Reflectance(float Nkd, float Nks, float NkdDiffuse, float NksDiffuse){
    kd=Nkd;
    ks=Nks;
    kdDiffuse=NkdDiffuse;
    ksDiffuse=NksDiffuse;
}