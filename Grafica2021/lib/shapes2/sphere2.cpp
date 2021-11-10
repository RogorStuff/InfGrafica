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

bool sphere::ray_intersect(ray r, colour& tono, float& distancia, vec3& normalParam) const{
    vec3 d = r.direccion;
    vec3 o = r.origen;

    vec3 oc = this->center;

    float a = dot(d, d);
    float b = dot(oc, d);
    float c = dot(oc, oc) - (this->radius * this->radius);
    float discriminant = (b * b) - ((a * c));
    if (discriminant > 0) {
        float temp = fabs((-b - sqrt(discriminant)) / a);
        float temp2 = fabs((-b + sqrt(discriminant)) / a);
        tono = this->color;
        if (temp > temp2) {
            distancia = temp2;
        }else{
            distancia = temp;
        }
            
        vec3 dondeGolpea = r.origen+(r.direccion*(distancia));
        //cout<<r.origen<<" "<<r.direccion<<endl;
        vec3 centro = this->center;
        vec3 normalGolpe = dondeGolpea-centro;     //Vector resultante de origen - golpe
        normalParam = normalizarPunto(normalGolpe);
        return true;
    } 
    return false;

/*
    vec3 p = this->center;
    vec3 po = o-p;
    double t = 1e-4;
    double b = dot(po, r.direccion);
    double det = b*b-dot(po, po)+this->radius*this->radius;
    if(det<0)return false;
    else det = sqrt(det);
    float A = b+det;
    float B = b-det;
    distancia = (A>B) ? B : A;
        vec3 dondeGolpea = r.origen+(r.direccion*(distancia));
        vec3 centro = this->center;
        vec3 normalGolpe = dondeGolpea-centro;     //Vector resultante de origen - golpe
        normalParam = normalizar(normalGolpe);
        tono = this->color;
        return true;*/

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