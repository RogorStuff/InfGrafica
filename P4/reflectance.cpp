#include "reflectance.hpp"

Reflectance::Reflectance(){
}

Reflectance::Reflectance(Pixel Nkd, Pixel Nks, Pixel NkdPhong, Pixel NksPhong, float Ns){
    kd=Nkd;
    ks=Nks;
    kdPhong=NkdPhong;
    ksPhong=NksPhong;
    s=Ns;
}