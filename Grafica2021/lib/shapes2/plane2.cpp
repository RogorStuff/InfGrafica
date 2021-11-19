#pragma once

#include "plane2.hpp"

plane::plane(){
}

plane::plane(vec3 center_,vec3 normal_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor){
    this->center=center_;
    this->normal=normal_;
    this->color=color_;
    this->diffuse=_diffuse;
    this->reflective=_reflective;
    this->refractive=_refractive;
    this->refractIndex=_refractIndex;
    this->emisor=_emisor;
}

vec3 plane::getCenter(){
    return this->center;
}

vec3 plane::getNormal(){
    return this->normal;
}

float plane::getDiffuse(){
    return this->diffuse;
}

float plane::getReflective(){
    return this->reflective;
}

float plane::getRefractive(){
    return this->refractive;
}

bool plane::getEmisor(){
    return this->emisor;
}


bool plane::ray_intersect(ray rayo, colour& tono, float& distancia, vec3& normalParam) const{

    vec3 l = rayo.direccion;
    vec3 po = this->center;
    vec3 lo = rayo.origen;
    vec3 n = this->normal;
    vec3 nNegado = negado(n);

    bool ret = false;
    float dist = 0.0;

    float denominator = dot(l, n);
    float denominator2 = dot(l, nNegado);

    if (denominator != 0.0) {
        vec3 aux = po-lo;
        dist = dot(aux, n) / denominator;
        if (dist > 0) {
            distancia = dist;
            tono = this->color;
            normalParam = n;
            ret = true;
        }
        
    } else if (denominator2 != 0.0) {
        vec3 aux = po-lo;
        dist = dot(aux, nNegado) / denominator2;
        if (dist > 0) {
            distancia = dist;
            tono = this->color;
            normalParam = nNegado;
            ret = true;
        }
    }
    return ret;
    
}

string plane::queSoy() const{
    return "plano";
}

void plane::material(float& Kd, float& Ks, float& Kr) const {
    Kd = this->diffuse;
    Ks = this->reflective;
    Kr = this->refractive;
}

bool plane::getEmisor() const {
    return emisor;
}

float plane::getRIndex() const {
    return this->refractIndex;
}