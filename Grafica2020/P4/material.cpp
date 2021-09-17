#pragma once

#include "material.hpp"


Material::Material() {
}

Material::Material(float kd_, float ks_, float kref_){
    kd = kd_;
    ks = ks_;
    krefraction = kref_;
}

Material Material::Emitter() {
    emisor = true;
}

Material Material::Reflector() {
    emisor = false;
}

bool Material::isEmissor(){
    return emisor;
}