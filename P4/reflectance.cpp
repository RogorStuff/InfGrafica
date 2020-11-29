#include "reflectance.hpp"

Reflectance::Reflectance(){
}

Reflectance::Reflectance(Pixel Nkd, Pixel Nks, Pixel NkdDiffuse, Pixel NksDiffuse){
    kd=Nkd;
    ks=Nks;
    kdDiffuse=NkdDiffuse;
    ksDiffuse=NksDiffuse;
}