#pragma once

#include "emission.hpp"
#include "image.hpp"
#include "pixel.hpp"
#include "plane.hpp"
#include "luzPuntual.hpp"

#ifndef sensor_HPP
#define sensor_HPP

using namespace std;

static const float localNearZero = 1e-6;

class Sensor{//Todos los planos deben mirar hacia la cámara
    public:
        Vectores coordenadasO;
        Vectores coordenadasU;
        Vectores coordenadasI;
        Vectores apunta;
        //Meter material
        Sensor();
        Sensor(Vectores CoordenadasO, Vectores CoordenadasU, Vectores CoordenadasI, Vectores NdistanciaPlano);
        void rotarSensor(float anguloX, float anguloY, float anguloZ);
        Pixel colorRayo(Ray ray, vector<Obstacle*> &entorno, vector<LuzPuntual*> &luces, bool &impactado);
        image ver(vector<Obstacle*> &entorno, vector<LuzPuntual*> &luces, string imagenNombre, int anchototal, int altoTotal);
    
};

#endif
