#include "lib/shapes2/plane2.cpp"
#include "lib/shapes2/sphere2.cpp"
#include "lib/shapes2/primitiva.hpp"
#include "lib/scene/camera.cpp"
#include "lib/scene/sceneRender.cpp"
#include "lib/shapes2/sceneReader2.cpp"
#include "lib/images/image.cpp"
#include "lib/images/texture.cpp"

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

    int numRayos = 3;
    int width = 1000;
    int height = 1000;
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
            std::cout << "ppp cambiados" << std::endl;
        }
        if (strcmp (argv[i], "width") == 0){
            width = atoi(argv[i+1]);
            widthCambiado = true;
            std::cout << "width cambiados" << std::endl;
        }
        if (strcmp (argv[i], "height") == 0){
            height = atoi(argv[i+1]);
            heightCambiado = true;
            std::cout << "height cambiados" << std::endl;
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

    Texture texturaBosque = Texture("forest.ppm");
    Texture texturaBosque2 = Texture("forest2.ppm");

    vector<sphere> esferas;
    vector<plane> planos;
    pointLight light = pointLight(vec3(0.0, 0.0, 0.0, 0), 0);
    bool exito = sceneReader(esferas, planos, light, "pruebaP4copy.txt");
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
        plane* a = new plane(p.center, p.normal, p.color, p.diffuse, p.reflective, p.refractive, p.refractIndex, p.emisor, p.min, p.max);

        if(a->normal.z<0){
            //Textura del cielo
            a->setTextura(texturaBosque);
        } else if (a->normal.y>0){
            //Suelo
            Texture texturaSuelo = Texture("snow ground.ppm");
            a->setTextura(texturaSuelo);
        } else if (a->normal.y<0){
            //Suelo
            Texture texturaSuelo = Texture("skysun.ppm");
            cout<<texturaSuelo.height<<" "<<texturaSuelo.width<<endl;
            a->setTextura(texturaSuelo);
        } else if (a->normal.x<0){
            //Pared derecha
            a->setTextura(texturaBosque2);
        } else if (a->normal.x>0){
            //Pared izquierda
            a->setTextura(texturaBosque2);
        }
        
        primitivas.push_back(a);
    } 


    if(exito){

        //Generamos la cámara
        
        vec3 sensorCentro(0.0, 0.0, 0.0, 1);
        vec3 sensorApuntaI(-1.0, 0.0, 0.0, 0);       //palado, x
        vec3 sensorApuntaU(0.0, -1.0, 0.0, 0);       //Parriba, y
        vec3 sensorApunta(0.0, 0.0, 1.0, 0);        //Palante, z
        
        camera sensor(sensorApuntaU, sensorApuntaI, sensorApunta, sensorCentro);

        if(light.potencia>0){
            cout<<"Tenemos luces puntuales"<<endl;
        }else{
            cout<<"Tenemos luces globales"<<endl;
        }

        vector<Pixel> textura;
        exito = textureReader(textura, "lantern.ppm");
        
        Image resultado = ver(primitivas, sensor, numRayos, filename, width, height, light, textura);
        resultado.save(filename);

    }else{
        cout<<"Ha habido un problema cargando la escena"<<endl;
    }

}