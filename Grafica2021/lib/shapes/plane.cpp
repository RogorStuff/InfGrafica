#pragma once

#include "plane.hpp"

plane::plane(){
}

plane::plane(vec3 center_,vec3 normal_, colour color_){
    this->center=center_;
    this->normal=normal_;
    this->color=color_;
}

vec3 plane::getCenter(){
    return this->center;
}

vec3 plane::getNormal(){
    return this->normal;
}

void plane::printCenter(){
    cout<<this->center.x<<" - "<<this->center.y<<" - "<<this->center.z;
}

void plane::printNormal(){
    cout<<this->normal.x<<" - "<<this->normal.y<<" - "<<this->normal.z;
}