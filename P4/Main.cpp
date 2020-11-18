#include "emission.hpp"
#include "image.hpp"
#include "pixel.hpp"
#include "sensor.hpp"
#include "plane.hpp"
#include "sphere.hpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include <time.h>

using namespace std;

/*
Pixel colorRayo(Ray ray, vector<Obstacle*> &entorno){

    Pixel pixelResultado(0.0, 0.0, 0.0);
    int rebotes = 0;
    bool sigueRebotando = true;
    Vectores origen = ray.origen;
    float BRDF = 1.0;

    while (sigueRebotando){

        bool impactado = false;
        Emission visto;
        float distancia;
        Pixel pixelaux;
        Obstacle* obstaculoGolpeado;
        float menorDistancia=1000000.0;


        for (auto obstacle : entorno){          //Calcula con que obstaculo golpea
            if(obstacle->ray_intersect(ray,visto,distancia)){ 
                impactado = true;
                if(distancia<menorDistancia){
                    obstaculoGolpeado = obstacle;
                    pixelaux.update(visto);
                    menorDistancia=distancia;
                }
            }
        }

        if (!impactado){    //Si no impacta con nada, termina
            pixelResultado.update(0.0, 0.0, 0.0);
            break;
        }else {  //Ha impactado con algun objeto:     p = o + rayo * distnacia
            Vectores nuevoOrigen(ray.origen, ray.direccion, menorDistancia);
            //Suponer siempre refractor: TODO POR SI ES LUZ

            //Calcular color:
                //TODO GENERAR COLOR CON BRDF Y ACTUALIZAR BRDF

            //Calcular nueva direccion de rebote:
                //TODO GENERAR DIRECCION

            //Actualizar rayo
                //TOOD actualizar direccion
            ray.origen = nuevoOrigen;

            rebotes++;  //Mira a ver si es el último rebote
            if (rebotes == 2){
                sigueRebotando = false;
            }
        }
                
    if (BRDF <= 0.0){   //Si se ha quedado sin luz el rayo
        sigueRebotando = false;
    }

    pixelResultado.divideTotal(rebotes); 
    return pixelResultado;
}
*/


int main () {
    srand (time(NULL));
    Vectores sensorCentro(0.0, 0.0, 0.0, 1);
    Vectores sensorApuntaF(0.0, 0.0, 1.0, 0);
    Vectores sensorApuntaI(1.0, 0.0, 0.0, 0);
    Vectores sensorApuntaU(0.0, 1.0, 0.0, 0);
    Sensor sensor(sensorCentro,sensorApuntaU,sensorApuntaI,sensorApuntaF);

    Vectores planoCentro1(4.0, 0.0, 4.0, 1);
    Vectores planoNormal1(-1.0, 0.0, 0.0, 0);
    Emission color1(1, 0, 0);
    Plane plano1(planoCentro1, planoNormal1, color1);
    
    Vectores planoCentro2(-4.0, 0.0, 4.0, 1);
    Vectores planoNormal2(1.0, 0.0, 0.0, 0);
    Emission color2(0, 1, 0);
    Plane plano2(planoCentro2, planoNormal2, color2);

    Vectores planoCentro3(0.0, 0.0, 8.0, 1);
    Vectores planoNormal3(0.0, 0.0, -1.0, 0);
    Emission color3(1, 1, 1);
    Plane plano3(planoCentro3, planoNormal3, color3);

    Vectores planoCentro4(0.0, -4.0, 4.0, 1);
    Vectores planoNormal4(0.0, 1.0, 0.0, 0);
    Emission color4(0, 0, 1);
    Plane plano4(planoCentro4, planoNormal4, color4);

    Vectores planoCentro5(0.0, 4.0, 4.0, 1);
    Vectores planoNormal5(0.0, -1.0, 0.0, 0);
    Emission color5(0, 0, 1);
    Plane plano5(planoCentro5, planoNormal5, color5);

    Vectores bolaAux1(0.0, 0.0, 5.0, 1);
    float radio = 2;
    Emission colorSphere(0.5, 0, 0.5);
    Sphere bola1(bolaAux1,radio,colorSphere);

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
