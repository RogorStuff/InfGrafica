#pragma once

#include "camera.hpp"

camera::camera(){}

camera::camera(vec3 CoordenadasO, vec3 CoordenadasU, vec3 CoordenadasI, vec3 NdistanciaPlano){
    coordenadasO=CoordenadasO;
    coordenadasU=CoordenadasU;
    coordenadasI=CoordenadasI;
    apunta=NdistanciaPlano;
}
    
void camera::rotarSensor(float anguloX, float anguloY, float anguloZ){
    coordenadasU = rotarX(anguloX, coordenadasU);
    coordenadasU = rotarY(anguloY, coordenadasU);
    coordenadasU = rotarZ(anguloZ, coordenadasU);
    coordenadasI = rotarX(anguloX, coordenadasI);
    coordenadasI = rotarY(anguloY, coordenadasI);
    coordenadasI = rotarZ(anguloZ, coordenadasI);
    apunta = rotarX(anguloX, apunta);
    apunta = rotarY(anguloY, apunta);
    apunta = rotarZ(anguloZ, apunta);
}