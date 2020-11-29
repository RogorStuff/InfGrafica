#include "reflectance.hpp"

#ifndef material_HPP
#define material_HPP

enum MATERIAL_TYPE {
    EMITTER,
    REFLECTOR
};

/*
 * EMMITER
 * Light area
 *
 * REFLECTOR
 * Reflector material
 * Perfect Diffuse material: kd = 0 AND ks = 0 AND ksPhong = kdPhong
 * Perfect Phong material: kd = 0 AND ks = 0
 * Perfect Delta material: kdPhong = 0 AND ksPhong = 0
 * Perfect Refractor material: ks = 0 AND kdPhong = 0 AND ksPhong = 0
 * Perfect Specular material: kd = 0 AND kdPhong = 0 AND ksPhong = 0
 */

class Material{
    public:
        MATERIAL_TYPE type;
        Reflectance reflectance;
        Material();
        Material Emitter();
        Material Reflector(Pixel kd, Pixel ks, Pixel kdDiffuse, Pixel ksDiffuse);
        Material Phong(Pixel kdDiffuse, Pixel ksDiffuse);
        Material Diffuse(Pixel k);
        Material Delta(Pixel kd, Pixel ks);
        Material Refractor(Pixel kd);
        Material Specular(Pixel ks);
};

#endif