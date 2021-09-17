#pragma once

#include <string>
#include <vector>
#include "vector.cpp"
#include "pixel.hpp"

class LuzPuntual {
    public:
        Vectores coordenada;
        Pixel color;
        float intensidad;
        
        LuzPuntual();
        LuzPuntual(Vectores coordenadaNueva);
};
