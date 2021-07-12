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

    int ppp = 100;
    int ancho = 300;
    int largo = 300;

    srand (time(NULL));
    
    Vectores sensorCentro(0.0, 0.0, 0.0, 1);
    Vectores sensorApuntaF(0.0, 0.0, 1.0, 0);
    Vectores sensorApuntaI(-1.0, 0.0, 0.0, 0);
    Vectores sensorApuntaU(0.0, -1.0, 0.0, 0);
    Sensor sensor(sensorCentro,sensorApuntaU,sensorApuntaI,sensorApuntaF);

    Material materialIluminado(0.0,0.0,0.0);
    materialIluminado.Emitter();
    Material materialReflector(1.0, 0.0, 0.0);
    materialReflector.Reflector();

    //Pared derecha
    Vectores planoCentro1(4.0, 0.0, 4.0, 1);
    Vectores planoNormal1(1.0, 0.0, 0.0, 0);
    Emission color1(1.0, 0.01, 0.01);
    Plane plano1(planoCentro1, planoNormal1, color1, materialReflector, 0.0);
    
    //Pared izquierda
    Vectores planoCentro2(-4.0, 0.0, 4.0, 1);
    Vectores planoNormal2(1.0, 0.0, 0.0, 0);
    Emission color2(0.01, 1.0, 0.01);
    Plane plano2(planoCentro2, planoNormal2, color2, materialReflector, 0.0);

    //Pared fondo
    Vectores planoCentro3(0.0, 0.0, 8.0, 1);
    Vectores planoNormal3(0.0, 0.0, 1.0, 0);
    Emission color3(0.7, 0.4, 0.01);
    Plane plano3(planoCentro3, planoNormal3, color3, materialReflector, 0.0);

    /*
    Vectores planoCentro6(0.0, 0.0, -2.0, 1);
    Vectores planoNormal6(0.0, 0.0, 1.0, 0);
    Emission color6(1.0, 1.0, 1.0);
    Plane plano6(planoCentro6, planoNormal6, color6, materialIluminado, 0.0);
    */

    //Suelo
    Vectores planoCentro4(0.0, -4.0, 4.0, 1);
    Vectores planoNormal4(0.0, 1.0, 0.0, 0);
    Emission color4(1.0, 1.0, 1.0);
    Plane plano4(planoCentro4, planoNormal4, color4, materialReflector, 0.0);

    //Techo
    Vectores planoCentro5(0.0, 4.0, 4.0, 1);
    Vectores planoNormal5(0.0, 1.0, 0.0, 0);
    Emission color5(1.0, 1.0, 1.0);
    Plane plano5(planoCentro5, planoNormal5, color5, materialIluminado, 0.0);
    
    //Pelota
    Vectores bolaAux1(0.0, 0.0, 5.0, 1);
    float radio = 1;
    Emission colorSphere(0.2, 0.7, 0.8);
    Sphere bola1(bolaAux1,radio,colorSphere, materialReflector, 0.0);


    Vectores origenLuzPuntual(0.0, 0.0, 7.9, 1);
    LuzPuntual luzpuntual(origenLuzPuntual);

    
    vector<LuzPuntual*> lucesPuntuales;
    lucesPuntuales.push_back(&luzpuntual);

    vector<Obstacle*> scene;
    scene.push_back(&plano1);
    scene.push_back(&plano2);
    scene.push_back(&plano3);
    scene.push_back(&plano4);
    scene.push_back(&plano5);
    //scene.push_back(&plano6);
    scene.push_back(&bola1);

    //image imagen("patata", true, 100, 100);
    image imagen = sensor.ver(scene, lucesPuntuales, "patata", ancho, largo, ppp);

    imagen.save("patata");
    
/*
//    Vectores planoB1(0.0, -1.0, -1.0, 0);
//    Vectores reflejo = diffuse(Vectores(0.0, 0.0, 1.0,0),planoB1,Vectores(0.0, 0.0, 1.0,1));
//    cout<<reflejo.c[0]<<" "<<reflejo.c[1]<<" "<<reflejo.c[2]<<endl;*/
    
}
