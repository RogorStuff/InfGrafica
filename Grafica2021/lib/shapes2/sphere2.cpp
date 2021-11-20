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

//http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
    vec3 d = r.direccion;
    vec3 o = r.origen;
    vec3 c = this->center;
    float r2 = this->radius;

    float t1, t2;

    vec3 L = c-o;
    float tca = dot(L, d);
    if(tca < 0) return false;

    float d2 = dot(L,L) - tca * tca;
    if (d2 > r2 * r2) return false; 

    float thc = sqrt(r2*r2-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if (t1 < 0) return false;
    }

    tono = this->color;
    distancia = t1;
    vec3 dondeGolpea = o+(d)*(distancia);
    vec3 normalGolpe = dondeGolpea-(c);     //Vector resultante de origen - golpe
    normalParam = normalizar(normalGolpe);
    return true;
   
}

//http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
bool sphere::ray_intersect2(ray r, colour& tono, float& distancia, vec3& normalParam) const{

    vec3 d = r.direccion;
    vec3 o = r.origen;
    vec3 c = this->center;
    float r2 = this->radius;

    float t1, t2;

    vec3 L = c-o;
    float tca = dot(L, d);
    if(tca < 0) return false;

    float d2 = dot(L,L) - tca * tca;
    if (d2 > r2 * r2) return false; 

    float thc = sqrt(r2*r2-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if (t1 < 0) return false;
    }

    tono = this->color;
    distancia = t2;
    vec3 dondeGolpea = o+(d)*(distancia);
    vec3 normalGolpe = dondeGolpea-(c);     //Vector resultante de origen - golpe
    normalParam = normalizar(normalGolpe);
    return true;
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