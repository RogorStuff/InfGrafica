#include "material.hpp"
#include "pixel.hpp"


Material::Material() {
}

Material Material::Emitter() {
    type = EMITTER;
}

Material Material::Reflector(Pixel kd, Pixel ks, float s, Pixel kdPhong, Pixel ksPhong) {
    type = REFLECTOR;
    reflectance = Reflectance(kd, ks, kdPhong, ksPhong, s);
}

Material Material::Phong(Pixel kdPhong, Pixel ksPhong, float s) {
    return Reflector(Pixel(0.0,0.0,0.0), Pixel(0.0,0.0,0.0), s, kdPhong, ksPhong);
}

Material Material::Diffuse(Pixel k) {
    return Phong(k, Pixel(0.0,0.0,0.0), 1);
}

Material Material::Delta(Pixel kd, Pixel ks) {
    return Reflector(kd, ks, 1, Pixel(0.0,0.0,0.0), Pixel(0.0,0.0,0.0));
}

Material Material::Refractor(Pixel kd) {
    return Delta(kd, Pixel(0.0,0.0,0.0));
}

Material Material::Specular(Pixel ks) {
    return Delta(Pixel(0.0,0.0,0.0), ks);
}