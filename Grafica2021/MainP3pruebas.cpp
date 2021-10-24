#include "lib/shapes/plane.cpp"
#include "lib/shapes/sphere.cpp"
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

    int numRayos = 140;

    vector<sphere> esferas;
    vector<plane> planos;

    bool exito = sceneReader(esferas, planos, "prueba.txt");

    if(exito){

        //Generamos la cámara
        
        vec3 sensorCentro(0.0, 0.0, 0.0, 1);
        vec3 sensorApuntaI(-1.0, 0.0, 0.0, 0);
        vec3 sensorApuntaU(0.0, -1.0, 0.0, 0);
        vec3 sensorApunta(0.0, 0.0, 1.0, 0);
        camera sensor(sensorApuntaU, sensorApuntaI, sensorApunta, sensorCentro);

        Image resultado = ver(esferas, planos, sensor, numRayos, "test", 100, 100);
        resultado.save("test");

    }else{
        cout<<"Ha habido un problema cargando la escena"<<endl;
    }

}

//plane 2 3.5 4 0 0 0 1.0 0.0 1.0