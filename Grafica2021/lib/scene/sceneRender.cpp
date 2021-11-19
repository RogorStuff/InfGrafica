#pragma once

#include "camera.cpp"
#include "ray.cpp"
#include "../math/matrix.cpp"
#include "../images/image.cpp"
#include "../images/pixel.cpp"
#include "../shapes2/plane2.cpp"
#include "../shapes2/sphere2.cpp"
#include "../shapes2/colour.cpp"
#include "../progressBar/progressBar.hpp"
#include "../pathtracing/newDirection.cpp"

#include <time.h>  
#include <stdlib.h> 
#include <random>
#include <iostream>

using namespace std;

matrix cameraToWorld;

Pixel colorPathR(vector<Primitiva*> &primitivas, ray rayoLanzado, int loop){

    if (loop == 2){
        //std::cout << "cortamos por loop" << std::endl;
        return Pixel(1.0, 1.0, 1.0);
    }

    colour visto = colour(0.0, 0.0, 0.0);
    float distanciaGolpe;
    float menorDistancia = INFINITY;
    Pixel resultado;
    bool golpea = false;
    vec3 vectorNormal;
    Primitiva* objetoGolpeado;
    for (Primitiva* p : primitivas){

        if (p->ray_intersect(rayoLanzado, visto, distanciaGolpe, vectorNormal)){
            golpea = true;
            if (distanciaGolpe < menorDistancia){
                resultado.update(visto);
                menorDistancia=distanciaGolpe;
                objetoGolpeado = p;
            }
        }
    }

    if (golpea){
        if (objetoGolpeado->getEmisor()){
            return resultado;
        } else {    //Objeto golpeado no emisor

            EVENT eventoObjeto;

            eventoObjeto = getRandomEvent(objetoGolpeado);
            
            if (eventoObjeto != DEAD){
                vec3 puntoChoque = desplazarPunto(rayoLanzado.origen, rayoLanzado.direccion, menorDistancia);
                vec3 newDirectionRay = generarDireccion(eventoObjeto, rayoLanzado.direccion, vectorNormal, puntoChoque, objetoGolpeado);
                //newDirectionRay = normalizar(newDirectionRay);    //Se normaliza en generarDireccion
                ray nuevoRayo = ray(puntoChoque, newDirectionRay);
                if (eventoObjeto == REFLECTION){
                    return (colorPathR(primitivas, nuevoRayo,loop+1));
                }else{
                    return (resultado * colorPathR(primitivas, nuevoRayo, loop+1));
                }
            }else{
                return Pixel(0.0, 0.0, 0.0);
            }
        }
    }
    return resultado;
}




Pixel colorPath(vector<Primitiva*> &primitivas, ray rayoLanzado, bool verbose){

    if (verbose){
        std::cout << "Yo que se, patata" << std::endl;
    }

    colour visto = colour(0.0, 0.0, 0.0);
    float distanciaGolpe;
    float menorDistancia = INFINITY;
    Pixel resultado;
    bool golpea = false;
    vec3 vectorNormal;
    Primitiva* objetoGolpeado;
    for (Primitiva* p : primitivas){

        if (p->ray_intersect(rayoLanzado, visto, distanciaGolpe, vectorNormal)){
            golpea = true;
            if (distanciaGolpe < menorDistancia){
                resultado.update(visto);
                menorDistancia=distanciaGolpe;
                objetoGolpeado = p;
            }
        }
    }

    if (golpea){
        if (objetoGolpeado->getEmisor()){
            return resultado;
        } else {    //Objeto golpeado no emisor
            EVENT eventoObjeto = getRandomEvent(objetoGolpeado);
            if (eventoObjeto != DEAD){
                vec3 puntoChoque = desplazarPunto(rayoLanzado.origen, rayoLanzado.direccion, menorDistancia);
                vec3 newDirectionRay = generarDireccion(eventoObjeto, rayoLanzado.direccion, vectorNormal, puntoChoque, objetoGolpeado);
                //newDirectionRay = normalizar(newDirectionRay);    //Se normaliza en generarDireccion
                ray nuevoRayo = ray(puntoChoque, newDirectionRay);
                if (eventoObjeto == REFLECTION){
                    std::cout << "CAGATE EN TU PUTA MADRE" << std::endl;
                    //return (colorPathR(primitivas, nuevoRayo, 1));
                }else{
                    // resultado = Pixel(0.0, 0.0, 0.0);
                    //return (resultado * colorPathR(primitivas, nuevoRayo, 1));
                    return (resultado * colorPath(primitivas, nuevoRayo, verbose));
                }
            }else{
                return Pixel(0.0, 0.0, 0.0);
            }
        }
    }

    return resultado;
}

Image ver(vector<Primitiva*> &primitivas, camera sensor, int numRayos, string imagenNombre, int anchototal, int altoTotal){
    Image imagen(imagenNombre, true, anchototal, altoTotal);         
    colour visto;
    Pixel pixel;
    float aux;

    srand (time(NULL));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 90.0);

    float imageAspectRatio = anchototal / (float)altoTotal; 
    matrix cameraToWorld(sensor.coordenadasU, sensor.coordenadasI, sensor.apunta, sensor.coordenadasO);
    cameraToWorld = matrix(sensor.coordenadasU, sensor.coordenadasI, sensor.apunta, sensor.coordenadasO);
    int totalPixeles = imagen.total;

    for (int miraPixel=0; miraPixel < totalPixeles; miraPixel++){
        //bar.update();
        
        float menorDistancia=INFINITY;
        bool impactado =false;
        int alto=miraPixel/imagen.height;
        int ancho=miraPixel%imagen.height;

        float y = (-2 * (alto + 0.05) / (float)anchototal + 1) * imageAspectRatio; 
        float x = (-1 + 2 * (ancho + 0.05) / (float)altoTotal); 

        vector<ray> rayos;  //Vector de todos los rayos lanzados a un pixel


        float pixelXSide = (float)2 / altoTotal;
        float pixelYSide = (float)2 / anchototal;
        float x2 =  (miraPixel / anchototal) * pixelXSide - 1.0;
        float y2 =  (miraPixel % anchototal) * pixelYSide - 1.0;

        for (int i=0; i<numRayos; i++){

            // Tomamos un punto del pixel dejando un margen de 5% por cada lado
            float X = (float)(dist(mt))/100;
            float Y = (float)(dist(mt))/100;
            //float X = (float)(50)/100;
            //float Y = (float)(50)/100;
            // Ponemos las coordenadas en la esquina superior izquierda y desplazamos dentro de dicho margen
            vec3 rayDirection(x+X/(float)anchototal, y+Y/(float)altoTotal, sensor.apunta.z, 0);
            rayDirection = normalizar(rayDirection);
            ray rayoAux(sensor.coordenadasO,rayDirection);
            // Añadimos rayo al conjunto total
            rayos.push_back(rayoAux);
        }

        vector<Pixel> recibidos;    //Tenemos todos los rayos, empezamos a mirar que color devuelve cada rayo
        double rayosLanzados = 0;
        double rayoAnalizar = (700*680+300)*numRayos;
        for (ray rayo : rayos){
            bool verbose = false;
            //if (rayosLanzados == rayoAnalizar) {
            //    verbose = true;
            //}
            
            Pixel devuelto = colorPath(primitivas, rayo, verbose);

            recibidos.push_back(devuelto);
            rayosLanzados++;
        }

        imagen.imageMatrix[miraPixel]=media(recibidos);

        if (miraPixel % 10000 == 0){
            cout << "\r" << "Calculados " << (float)miraPixel*100/totalPixeles << " % de pixeles     ";
        }
    }
    cout << "\r" << "Calculados " << "100" << " % de pixeles     " << endl;
    return imagen;
}