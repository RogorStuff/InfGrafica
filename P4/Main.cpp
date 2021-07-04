#include "emission.cpp"
#include "image.cpp"
#include "pixel.cpp"
#include "sensor.cpp"
#include "plane.cpp"
#include "sphere.cpp"
#include "material.cpp"
#include "ray.cpp"
#include "luzPuntual.cpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;


//Copmilar: g++ -std=c++11 Main.cpp -o a
int main () {
    srand (time(NULL));
    
    Vectores sensorCentro(0.0, 0.0, 0.0, 1);
    Vectores sensorApuntaF(0.0, 0.0, 1.0, 0);
    Vectores sensorApuntaI(-1.0, 0.0, 0.0, 0);
    Vectores sensorApuntaU(0.0, -1.0, 0.0, 0);
    Sensor sensor(sensorCentro,sensorApuntaU,sensorApuntaI,sensorApuntaF);

    Material materialIluminado;
    materialIluminado.Emitter();
    Material materialReflector;
    materialReflector.Reflector();

    //Pared derecha
    Vectores planoCentro1(4.0, 0.0, 4.0, 1);
    Vectores planoNormal1(-1.0, 0.0, 0.0, 0);
    Emission color1(1, 0, 0);
    Plane plano1(planoCentro1, planoNormal1, color1, materialReflector, 0.0);
    
    //Pared izquierda
    Vectores planoCentro2(-4.0, 0.0, 4.0, 1);
    Vectores planoNormal2(1.0, 0.0, 0.0, 0);
    Emission color2(0, 1, 0);
    Plane plano2(planoCentro2, planoNormal2, color2, materialReflector, 0.0);

    //Pared fondo
    Vectores planoCentro3(0.0, 0.0, 8.0, 1);
    Vectores planoNormal3(0.0, 0.0, -1.0, 0);
    Emission color3(1, 1, 1);
    Plane plano3(planoCentro3, planoNormal3, color3, materialReflector, 0.0);

    //Suelo
    Vectores planoCentro4(0.0, -4.0, 4.0, 1);
    Vectores planoNormal4(0.0, 1.0, 0.0, 0);
    Emission color4(0, 0, 1);
    Plane plano4(planoCentro4, planoNormal4, color4, materialIluminado, 0.0);

    //Techo
    Vectores planoCentro5(0.0, 4.0, 4.0, 1);
    Vectores planoNormal5(0.0, -1.0, 0.0, 0);
    Emission color5(0.5, 0, 0.5);
    Plane plano5(planoCentro5, planoNormal5, color5, materialReflector, 0.0);
    
    Vectores bolaAux1(0.0, 0.0, 4.0, 1);
    float radio = 1;
    Emission colorSphere(0.5, 0, 0.5);
    Sphere bola1(bolaAux1,radio,colorSphere, materialReflector, 0.0);


    Vectores origenLuzPuntual(0.0, 0.0, 7, 1);
    LuzPuntual luzpuntual(origenLuzPuntual);

    
    Vectores bolaAux2(0.0, 0.0, 7, 1);
    float radio2 = 0.2;
    Emission colorSphere2(0.8, 0, 0.2);
    Sphere bola2(bolaAux2,radio2,colorSphere2, materialReflector, 0.0);

    vector<LuzPuntual*> lucesPuntuales;
    lucesPuntuales.push_back(&luzpuntual);

    vector<Obstacle*> scene;
    scene.push_back(&plano1);
    scene.push_back(&plano2);
    scene.push_back(&plano3);
    scene.push_back(&plano4);
    scene.push_back(&plano5);
    scene.push_back(&bola1);
    scene.push_back(&bola2);

    //image imagen("patata", true, 100, 100);
    image imagen = sensor.ver(scene, lucesPuntuales, "patata", 100, 100);

    imagen.save("patata");
    
}
