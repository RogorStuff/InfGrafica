#include "lib/shapes/plane.cpp"
#include "lib/shapes/sphere.cpp"
#include "lib/shapes/primitiva.hpp"
#include "lib/scene/camera.cpp"
#include "lib/scene/sceneRender.cpp"
#include "lib/shapes/sceneReader.cpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

//Compilar: g++ -std=c++11 MainP3pruebas.cpp -o a -O3

int main () {


    int numRayos = 150;

    vector<sphere> esferas;
    vector<plane> planos;
    bool exito = sceneReader(esferas, planos, "prueba.txt");

    
    //Cargamos el vector de primitivas con las esferas y planos anteriores
    vector<Primitiva*> primitivas;
    for(int i = 0; i< esferas.size(); i++){
        sphere s = esferas.at(i);
        sphere* a = new sphere(s.center, s.radius, s.color);
        primitivas.push_back(a);
    } 
    for(int i = 0; i< planos.size(); i++){
        plane p = planos.at(i);
        plane* a = new plane(p.center, p.normal, p.color);
        primitivas.push_back(a);
    } 


    if(exito){

        //Generamos la cámara
        
        vec3 sensorCentro(0.0, 0.0, 0.0, 1);
        vec3 sensorApuntaI(-1.0, 0.0, 0.0, 0);
        vec3 sensorApuntaU(0.0, -1.0, 0.0, 0);
        vec3 sensorApunta(0.0, 0.0, 1.0, 0);
        camera sensor(sensorApuntaU, sensorApuntaI, sensorApunta, sensorCentro);

        Image resultado = ver(primitivas, sensor, numRayos, "test", 2000, 2000);
        resultado.save("test");

    }else{
        cout<<"Ha habido un problema cargando la escena"<<endl;
    }

}

//plane 2 3.5 4 0 0 0 1.0 0.0 1.0