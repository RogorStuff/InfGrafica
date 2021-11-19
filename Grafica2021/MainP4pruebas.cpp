#include "lib/shapes2/plane2.cpp"
#include "lib/shapes2/sphere2.cpp"
#include "lib/shapes2/primitiva.hpp"
#include "lib/scene/camera.cpp"
#include "lib/scene/sceneRender.cpp"
#include "lib/shapes2/sceneReader2.cpp"
#include "lib/images/image.cpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <time.h>

using namespace std;

//Compilar: g++ -std=c++11 MainP4pruebas.cpp -o a -O3

//Ejecutar ppp PPP width WIDTH height HEIGHT filename FILENAME resolution RESOLUTION

int main (int argc, char *argv[]) {
    srand (time(NULL));

    int numRayos = 10;
    int width = 2000;
    int height = 2000;
    string filename = "salida";
    int resolution = 0;
    char rayosCambiados = false;
    char widthCambiado = false;
    char heightCambiado = false;
    char filenameCambiado = false;
    char resolutionCambiado = false;

    for (int i = 1; i < argc; i++){
        if (strcmp (argv[i], "ppp") == 0){
            numRayos = atoi(argv[i+1]);
            rayosCambiados = true;
        }
        if (strcmp (argv[i], "width") == 0){
            width = atoi(argv[i+1]);
            widthCambiado = true;
        }
        if (strcmp (argv[i], "height") == 0){
            height = atoi(argv[i+1]);
            heightCambiado = true;
        }
        if (strcmp (argv[i], "filename") == 0){
            filename = (argv[i+1]);
            filenameCambiado = true;
        }
        if (strcmp (argv[i], "resolution") == 0){
            resolution = atoi(argv[i+1]);
            resolutionCambiado = true;
        }
    }

    vector<sphere> esferas;
    vector<plane> planos;
    bool exito = sceneReader(esferas, planos, "pruebaP4.txt");
    cout<<"Tenemos "<<esferas.size()<<" esferas y "<<planos.size()<<" planos."<<endl;
    
    //Cargamos el vector de primitivas con las esferas y planos anteriores
    vector<Primitiva*> primitivas;
    for(int i = 0; i< esferas.size(); i++){
        sphere s = esferas.at(i);
        sphere* a = new sphere(s.center, s.radius, s.color, s.diffuse, s.reflective, s.refractive, s.refractIndex, s.emisor);
        primitivas.push_back(a);
    } 
    for(int i = 0; i< planos.size(); i++){
        plane p = planos.at(i);        
        plane* a = new plane(p.center, p.normal, p.color, p.diffuse, p.reflective, p.refractive, p.refractIndex, p.emisor);
        primitivas.push_back(a);
    } 


    if(exito){

        //Generamos la cámara
        
        vec3 sensorCentro(0.0, 0.0, 0.0, 1);
        vec3 sensorApuntaI(1.0, 0.0, 0.0, 0);       //palado, x
        vec3 sensorApuntaU(0.0, 1.0, 0.0, 0);       //Parriba, y
        vec3 sensorApunta(0.0, 0.0, 1.0, 0);        //Palante, z
        
        camera sensor(sensorApuntaU, sensorApuntaI, sensorApunta, sensorCentro);

        /*
        vec3 rayDirection(0.5, -0.8, sensor.apunta.z, 0);
        //matrix cameraToWorld(sensor.coordenadasU, sensor.coordenadasI, sensor.apunta, sensor.coordenadasO);
        //rayDirection = translation(cameraToWorld, rayDirection);
        ray rayoAux(sensor.coordenadasO,rayDirection);
        colour colorAux;
        float distnaciaAux;
        vec3 normalAux;
        for (int i=0; i<primitivas.size();i++){
            bool testEsfera = primitivas.at(i)->ray_intersect(rayoAux, colorAux, distnaciaAux, normalAux);
            if(testEsfera && primitivas.at(i)->queSoy()=="esfera"){
                float kd, ks, kr;
                primitivas.at(i)->material(kd, ks, kr);
                cout<<"Soy "<<primitivas.at(i)->queSoy()<<endl;
                cout<<"Material "<<kd<<" "<<ks<<" "<<kr<<" "<<endl;
                cout<<normalAux<<" y distancia "<<distnaciaAux<<endl;
            }
        }
        */
        
        
        Image resultado = ver(primitivas, sensor, numRayos, filename, width, height);
        resultado.save(filename);
        

    }else{
        cout<<"Ha habido un problema cargando la escena"<<endl;
    }

}

//plane 2 3.5 4 0 0 0 1.0 0.0 1.0