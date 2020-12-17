//#include "emission.hpp"
//#include "image.hpp"
//#include "pixel.hpp"
#include "sensor.hpp"
//#include "plane.hpp"
//#include "sphere.hpp"
//#include "material.hpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include <time.h>

using namespace std;

int main () {
    srand (time(NULL));
    
    Vectores sensorCentro(0.0, 0.0, 0.0, 1);
    Vectores sensorApuntaF(0.0, 0.0, 1.0, 0);
    Vectores sensorApuntaI(1.0, 0.0, 0.0, 0);
    Vectores sensorApuntaU(0.0, 1.0, 0.0, 0);
    Sensor sensor(sensorCentro,sensorApuntaU,sensorApuntaI,sensorApuntaF);

    Material materialIluminado;
    materialIluminado.Emitter();
    Material materialReflector;
    materialReflector.Reflector(float(0.1), float(0.1), float(0.9), float(0.1));

    Vectores planoCentro1(4.0, 0.0, 4.0, 1);
    Vectores planoNormal1(-1.0, 0.0, 0.0, 0);
    Emission color1(1, 0, 0);
    Plane plano1(planoCentro1, planoNormal1, color1, materialReflector, 0.0);//Add material y float nrefractiveinter
    
    Vectores planoCentro2(-4.0, 0.0, 4.0, 1);
    Vectores planoNormal2(1.0, 0.0, 0.0, 0);
    Emission color2(0, 1, 0);
    Plane plano2(planoCentro2, planoNormal2, color2, materialReflector, 0.0);//Add material y float nrefractiveinter

    Vectores planoCentro3(0.0, 0.0, 8.0, 1);
    Vectores planoNormal3(0.0, 0.0, -1.0, 0);
    Emission color3(1, 1, 1);
    Plane plano3(planoCentro3, planoNormal3, color3, materialReflector, 0.0);//Add material y float nrefractiveinter

    Vectores planoCentro4(0.0, -4.0, 4.0, 1);
    Vectores planoNormal4(0.0, 1.0, 0.0, 0);
    Emission color4(0, 0, 1);
    Plane plano4(planoCentro4, planoNormal4, color4, materialReflector, 0.0);//Add material y float nrefractiveinter

    //Techo
    Vectores planoCentro5(0.0, 4.0, 4.0, 1);
    Vectores planoNormal5(0.0, -1.0, 0.0, 0);
    Emission color5(0, 0, 1);
    Plane plano5(planoCentro5, planoNormal5, color5, materialIluminado, 0.0);//Add material y float nrefractiveinter
    
    Vectores bolaAux1(0.0, 0.0, 5.0, 1);
    float radio = 2;
    Emission colorSphere(0.5, 0, 0.5);
    Sphere bola1(bolaAux1,radio,colorSphere, materialReflector, 0.0);//Add material y float nrefractiveinter

    vector<Obstacle*> scene;
    scene.push_back(&plano1);
    scene.push_back(&plano2);
    scene.push_back(&plano3);
    scene.push_back(&plano4);
    scene.push_back(&plano5);
    scene.push_back(&bola1);
    Image imagen("patata", true, 200, 200);
    imagen = sensor.ver(scene, "patata", 200, 200);

    imagen.save("patata");
    
}
