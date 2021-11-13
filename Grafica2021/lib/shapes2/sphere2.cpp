#pragma once

#include "sphere2.hpp"

sphere::sphere(){
}

sphere::sphere(vec3 center_, float radius_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor){
    this->center=center_;
    this->radius=radius_;
    this->color=color_;
    this->diffuse=_diffuse;
    this->reflective=_reflective;
    this->refractive=_refractive;
    this->refractIndex=_refractIndex;
    this->emisor=_emisor;
}

vec3 sphere::getCenter(){
    return this->center;
}

float sphere::getRadius(){
    return this->radius;
}

float sphere::getDiffuse(){
    return this->diffuse;
}

float sphere::getReflective(){
    return this->reflective;
}

float sphere::getRefractive(){
    return this->refractive;
}

bool sphere::getEmisor(){
    return this->emisor;
}

//https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
bool sphere::ray_intersect(ray r, colour& tono, float& distancia, vec3& normalParam) const{
    vec3 d = (r.direccion);
    vec3 o = (r.origen);
    vec3 oc =(this->center);
    vec3 oc2 = (o-oc);

    float a = dot(d, d);
    float b = 2*dot(d, oc2);
    float c = dot(oc2, oc2) - (this->radius * this->radius);
    float discriminant = (b * b) - (4*(a * c));
    if (discriminant > 0) {
        float temp = (-(b + sqrt(discriminant)) / 2*a);
        float temp2 = (-(b - sqrt(discriminant)) / 2*a);
        if ((temp) > (temp2)) {
            distancia = (temp2);
        }else{
            distancia = (temp);
        }
            
        tono = this->color;
        vec3 dondeGolpea = desplazarPunto(o, d, distancia);
        distancia = fabs(distancia);
        vec3 centro = this->center;
        vec3 normalGolpe = vector2puntos(centro, dondeGolpea);     //Vector resultante de origen - golpe
        normalParam = normalGolpe;
        //normalParam = normalizar(normalGolpe);
        return true;
    } 
    return false;

}

string sphere::queSoy() const{
    return "esfera";
}

void sphere::material(float& Kd, float& Ks, float& Kr) const {
    Kd = this->diffuse;
    Ks = this->reflective;
    Kr = this->refractive;
}

bool sphere::getEmisor() const {
    return emisor;
}

float sphere::getRIndex() const {
    return this->refractIndex;
}