#pragma once

#include "camera.cpp"
#include "ray.cpp"
#include "../math/matrix.cpp"
#include "../images/image.cpp"
#include "../images/pixel.cpp"
#include "../shapes/plane.cpp"
#include "../shapes/sphere.cpp"
#include "../shapes/colour.cpp"
#include "../progressBar/progressBar.hpp"

#include <time.h>  
#include <stdlib.h> 
#include <random>
#include <iostream>

using namespace std;

Image ver(vector<Primitiva*> &primitivas, camera sensor, int numRayos, string imagenNombre, int anchototal, int altoTotal){
        Image imagen(imagenNombre, true, anchototal, altoTotal);        
        colour visto;
        Pixel pixel;
        float aux;

        srand (time(NULL));
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(5.0, 95.0);

        float imageAspectRatio = anchototal / (float)altoTotal; 
        matrix cameraToWorld(sensor.coordenadasU, sensor.coordenadasI, sensor.apunta, sensor.coordenadasO);
        int totalPixeles = imagen.total;
        //cout << "Creada barra de " << totalPixeles << endl;
        //progressbar bar(totalPixeles);
        //bar.set_todo_char(" ");
        //bar.set_done_char("*");
        //bar.set_opening_bracket_char("[");
        //bar.set_closing_bracket_char("]");

        for (int miraPixel=0; miraPixel < totalPixeles; miraPixel++){
            //bar.update();
            
            float menorDistancia=INFINITY;
            bool impactado =false;
            int alto=miraPixel/imagen.height;
            int ancho=miraPixel%imagen.height;

            float x = (2 * (alto + 0.05) / (float)anchototal - 1) * imageAspectRatio; 
            float y = (1 - 2 * (ancho + 0.05) / (float)altoTotal); 

            vector<ray> rayos;  //Vector de todos los rayos lanzados a un pixel

            for (int i=0; i<numRayos; i++){

                // Tomamos un punto del pixel dejando un margen de 5% por cada lado
                float X = (float)(dist(mt))/100;
                float Y = (float)(dist(mt))/100;
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

                for (Primitiva* p : primitivas){
                    if (p->ray_intersect(rayo, visto, aux)){
                        impactado = true;
                        if (aux < menorDistancia){
                            pixel.update(visto);
                            menorDistancia=aux;
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

            if (miraPixel % 100000 == 0){
                cout << "Calculados " << (float)miraPixel*100/totalPixeles << " % de pixeles" << endl;
            }
        }
        cout << "Calculados " << "100" << " % de pixeles" << endl;
        return imagen;
    }