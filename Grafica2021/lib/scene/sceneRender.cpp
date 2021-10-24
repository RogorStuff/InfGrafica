#pragma once

#include "camera.cpp"
#include "ray.cpp"
#include "../math/matrix.cpp"
#include "../images/image.cpp"
#include "../images/pixel.cpp"
#include "../shapes/plane.cpp"
#include "../shapes/sphere.cpp"
#include "../shapes/colour.cpp"

#include <time.h>  
#include <stdlib.h> 

using namespace std;

Image ver(vector<sphere> &entornoEsferas, vector<plane> &entornoPlanos, camera sensor, int numRayos, string imagenNombre, int anchototal, int altoTotal){
        Image imagen(imagenNombre, true, anchototal, altoTotal);        
        colour visto;
        Pixel pixel;
        float aux;

        srand (time(NULL));

        float imageAspectRatio = anchototal / (float)altoTotal; 
        matrix cameraToWorld(sensor.coordenadasU, sensor.coordenadasI, sensor.apunta, sensor.coordenadasO);

        for (int miraPixel=0; miraPixel < imagen.total; miraPixel++){
            
            float menorDistancia=INFINITY;
            bool impactado =false;
            int alto=miraPixel/imagen.height;
            int ancho=miraPixel%imagen.height;

            float x = (2 * (alto + 0.05) / (float)anchototal - 1) * imageAspectRatio; 
            float y = (1 - 2 * (ancho + 0.05) / (float)altoTotal); 

            vector<ray> rayos;

            for (int i=0; i<numRayos; i++){

                // Tomamos un punto del pixel dejando un margen de 5% por cada lado
                float X = (float)((rand() % 90)+5)/100;
                float Y = (float)((rand() % 90)+5)/100;
                // Ponemos las coordenadas en la esquina superior izquierda y desplazamos dentro de dicho margen
                vec3 rayDirection(x+X/(float)anchototal, y+Y/(float)altoTotal, sensor.apunta.z, 0);
                // Generar rayo
                rayDirection = translation(cameraToWorld, rayDirection);
                ray rayoAux(sensor.coordenadasO,rayDirection);
                // Añadimos rayo al conjunto total
                rayos.push_back(rayoAux);
            }

            vector<Pixel> recibidos;
            for (ray rayo : rayos){
                if(!entornoPlanos.empty()){
                    for (plane obstacle : entornoPlanos){
                        if(obstacle.ray_intersect(rayo,visto,aux)){ 
                            impactado = true;
                            if(aux<menorDistancia){
                                pixel.update(visto);
                                menorDistancia=aux;
                            }
                        }
                    }
                }
                if(!entornoEsferas.empty()){
                    for (sphere obstacle : entornoEsferas){
                        if(obstacle.ray_intersect(rayo,visto,aux)){ 
                            impactado = true;
                            if(aux<menorDistancia){
                                pixel.update(visto);
                                menorDistancia=aux;
                            }
                        }
                    }
                }
                if(impactado){
                    recibidos.push_back(pixel);
                }
            }

            if (impactado){
                imagen.imageMatrix[miraPixel]=media(recibidos);
            }else{
                //cout<<"No impacta";
            }
        }
        return imagen;
    }