#pragma once

#include "material.hpp"


Material::Material() {
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