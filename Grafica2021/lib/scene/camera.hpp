#pragma once

#include "math.h"
#include "../math/vec3.cpp"
#include "../math/matrix.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

#ifndef camera_HPP
#define camera_HPP

class camera {
    public:
        vec3 coordenadasO;
        vec3 coordenadasU;
        vec3 coordenadasI;
        vec3 apunta;
        camera();
        camera(vec3 CoordenadasO, vec3 CoordenadasU, vec3 CoordenadasI, vec3 NdistanciaPlano);
        void rotarSensor(float anguloX, float anguloY, float anguloZ);
        
};

#endif