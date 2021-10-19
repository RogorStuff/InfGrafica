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
