#include "obstacle.hpp"
#include "emission.hpp"
#include "image.hpp"

#ifndef sensor_HPP
#define sensor_HPP

using namespace std;

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
        Image ver(vector<Obstacle*> &entorno, string imagenNombre, int anchototal, int altoTotal);
    
};

#endif sensor_HPP
