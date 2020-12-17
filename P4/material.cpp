#include "material.hpp"


Material::Material() {
}

Material Material::Emitter() {
    emisor = true;
}

Material Material::Reflector(float kd, float ks, float kdDiffuse, float ksDiffuse) {
    emisor = false;
    reflectance = Reflectance(kd, ks, kdDiffuse, ksDiffuse);
}

bool Material::isEmissor(){
    return emisor;
}
/*
Material Material::Phong(Pixel kdDiffuse, Pixel ksDiffuse) {
    return Reflector(Pixel(0.0,0.0,0.0), Pixel(0.0,0.0,0.0), kdDiffuse, ksDiffuse);
}

Material Material::Diffuse(Pixel k) {
    return Phong(k, Pixel(0.0,0.0,0.0));
}

Material Material::Delta(Pixel kd, Pixel ks) {
    return Reflector(kd, ks, Pixel(0.0,0.0,0.0), Pixel(0.0,0.0,0.0));
}

Material Material::Refractor(Pixel kd) {
    return Delta(kd, Pixel(0.0,0.0,0.0));
}

Material Material::Specular(Pixel ks) {
    return Delta(Pixel(0.0,0.0,0.0), ks);
}*/