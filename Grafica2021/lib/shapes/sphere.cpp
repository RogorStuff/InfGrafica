#pragma once

#include "sphere.hpp"

sphere::sphere(){
}

sphere::sphere(vec3 center_, float radius_, colour color_){
    this->center=center_;
    this->radius=radius_;
    this->color=color_;
}

vec3 sphere::getCenter(){
    return this->center;
}

float sphere::getRadius(){
    return this->radius;
}

bool sphere::ray_intersect(ray& r, colour& tono, float& distancia) const{
    vec3 d = r.direccion;
    vec3 o = r.origen;

    vec3 oc = this->center;

    float t_min = -1;
    float t_max = 999999999999999;

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
            return true;
        }
        distancia = temp;
        return true;
    } 
    return false;
};

string sphere::queSoy() const{
    return "esfera";
}