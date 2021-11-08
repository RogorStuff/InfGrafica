#pragma once

#include "plane2.hpp"

plane::plane(){
}

plane::plane(vec3 center_,vec3 normal_, colour color_, float _diffuse, float _reflective, float _refractive, bool _emisor){
    this->center=center_;
    this->normal=normal_;
    this->color=color_;
    this->diffuse=_diffuse;
    this->reflective=_reflective;
    this->refractive=_refractive;
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


bool plane::ray_intersect(ray& rayo, colour& tono, float& distancia) const{
    float t_min = 0;
    float t_max = 99999999;

    vec3 l = rayo.direccion;
    vec3 po = this->center;
    vec3 lo = rayo.origen;
    vec3 n = normal;
    vec3 nNegado = negado(n);

    bool ret = false;

    float dist = 0.0;

    float denominator = dot(l, n);
    float denominator2 = dot(l, nNegado);


    if (denominator != 0) {
        vec3 aux = vector2puntos(lo, po);
        dist = dot(aux, n) / denominator;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            tono = this->color;
            ret = true;
        }
    } else if (denominator2 != 0) {
        vec3 aux = vector2puntos(lo, po);
        dist = dot(aux, n) / denominator2;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            tono = this->color;
            ret = true;
        }
    }else{
        //cout<<"HUGE FUCK"<<endl;
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