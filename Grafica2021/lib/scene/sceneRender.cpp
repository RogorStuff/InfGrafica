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

Pixel colorPathR(vector<Primitiva*> &primitivas, ray rayoLanzado, int loop, bool esrefl){
    colour visto = colour(0.0, 0.0, 0.0);
    float distanciaGolpe;
    float menorDistancia = INFINITY;
    Pixel resultado;
    bool golpea = false;
    vec3 vectorNormal;
    vec3 normalFinal;
    Primitiva* objetoGolpeado;
    for (Primitiva* p : primitivas){

        if (p->ray_intersect(rayoLanzado, visto, distanciaGolpe, vectorNormal)){
            golpea = true;
            if (distanciaGolpe < menorDistancia){
                resultado.update(visto);
                menorDistancia=distanciaGolpe;
                objetoGolpeado = p;
                normalFinal = vectorNormal;
            }
        }
    }


    if (esrefl){
        return resultado;
    }


    if (golpea){
        if (objetoGolpeado->getEmisor()){
            return resultado;
        } else {    //Objeto golpeado no emisor

            EVENT eventoObjeto;
            if (loop<2){
                eventoObjeto = getRandomEvent(objetoGolpeado);
                while (eventoObjeto==DEAD){
                    eventoObjeto = getRandomEvent(objetoGolpeado);
                }
            }
            //eventoObjeto = getRandomEvent(objetoGolpeado);
            
            if (eventoObjeto != DEAD){
                vec3 puntoChoque = desplazarPunto(rayoLanzado.origen, rayoLanzado.direccion, menorDistancia);
                vec3 newDirectionRay = generarDireccion(eventoObjeto, rayoLanzado.direccion, normalFinal, puntoChoque, objetoGolpeado);
                //newDirectionRay = normalizar(newDirectionRay);    //Se normaliza en generarDireccion
                ray nuevoRayo = ray(puntoChoque, newDirectionRay);
                if (eventoObjeto == REFLECTION){
                    //cout<<"Reflejo con Nuevo origen: "<<puntoChoque<<" y nueva direccion "<<newDirectionRay<<endl;
                    return (colorPathR(primitivas, nuevoRayo,loop+1, false));
                }else{
                    return (resultado * colorPathR(primitivas, nuevoRayo, loop+1, false));
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
    vec3 normalFinal;
    Primitiva* objetoGolpeado;
    for (Primitiva* p : primitivas){

        if (p->ray_intersect(rayoLanzado, visto, distanciaGolpe, vectorNormal)){
            golpea = true;
            if (distanciaGolpe < menorDistancia){
                resultado.update(visto);
                menorDistancia=distanciaGolpe;
                objetoGolpeado = p;
                normalFinal = vectorNormal;
            }
        }
    }

    if (golpea){
        if (objetoGolpeado->getEmisor()){
            return resultado;
        } else {    //Objeto golpeado no emisor
            EVENT eventoObjeto = getRandomEvent2(objetoGolpeado);
            if (eventoObjeto != DEAD){
                vec3 puntoChoque = desplazarPunto(rayoLanzado.origen, rayoLanzado.direccion, menorDistancia);
                vec3 newDirectionRay = generarDireccion(eventoObjeto, rayoLanzado.direccion, normalFinal, puntoChoque, objetoGolpeado);
                //newDirectionRay = normalizar(newDirectionRay);    //Se normaliza en generarDireccion
                ray nuevoRayo = ray(puntoChoque, newDirectionRay);
                if (eventoObjeto == REFLECTION){
                    if(objetoGolpeado->queSoy()=="esfera"){
                        //cout<<"Entra con "<<rayoLanzado.direccion<<" y normal "<<vectorNormal;
                    }
                    return (colorPathR(primitivas, nuevoRayo, 1, false));
                }else{
                    //resultado = Pixel(1.0, 0.0, 0.0);
                    return (resultado * colorPathR(primitivas, nuevoRayo, 1, false));
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
    //matrix cameraToWorld(sensor.coordenadasU, sensor.coordenadasI, sensor.apunta, sensor.coordenadasO);
    cameraToWorld = matrix(sensor.coordenadasI, sensor.coordenadasU, sensor.apunta, sensor.coordenadasO);
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

        /*
        //-----------MARCOS
        float pixelXSide = (float)2 / altoTotal;
        float pixelYSide = (float)2 / anchototal;
        float x2 =  (miraPixel / anchototal) * pixelXSide - 1.0;        //No se si es ancho o alto pero jaja salu2
        float y2 =  (miraPixel % anchototal) * pixelYSide - 1.0;        //No se si es ancho o alto pero jaja salu2
        //----------MARCOS
        */
        for (int i=0; i<numRayos; i++){
            /*
            //--------------MARCOS
            float xIter = x2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((x2 + pixelXSide) - x2)));
            float yIter = y2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((y2 + pixelYSide) - y2)));
            vec3 image_point = vec3(xIter, yIter, -sensor.apunta.z, 1);
            matrix baseChange2 = matrix(sensor.coordenadasI, sensor.coordenadasU ,sensor.apunta, sensor.coordenadasO);        // ES POSIBLE QUE HAY QUE CAMBIAR I E U
            vec3 p2 = baseChange(baseChange2, image_point);
            vec3 dir2 = vec3(p2.x - sensor.coordenadasO.x, p2.y - sensor.coordenadasO.y, p2.z - sensor.coordenadasO.z, 0);
            ray rayoActual2 = ray(sensor.coordenadasO, vec3(dir2.x / dir2.modulo(), dir2.y / dir2.modulo(), dir2.z / dir2.modulo(), 0));
            rayos.push_back(rayoActual2);
            //--------------NARCOS*/
            
            // Tomamos un punto del pixel dejando un margen de 5% por cada lado
            float X = (float)(dist(mt))/100;
            float Y = (float)(dist(mt))/100;
            //float X = (float)(50)/100;
            //float Y = (float)(50)/100;
            // Ponemos las coordenadas en la esquina superior izquierda y desplazamos dentro de dicho margen
            vec3 rayDirection(x, y, sensor.apunta.z, 0);
            rayDirection = baseChange(cameraToWorld, rayDirection);
            rayDirection = normalizar(rayDirection-sensor.coordenadasO);
            ray rayoAux(sensor.coordenadasO,rayDirection);
            // Añadimos rayo al conjunto total
            rayos.push_back(rayoAux);
        }

        vector<Pixel> recibidos;    //Tenemos todos los rayos, empezamos a mirar que color devuelve cada rayo
        //double rayosLanzados = 0;
        //double rayoAnalizar = (anchototal*680+300)*numRayos;
        for (ray rayo : rayos){
            bool verbose = false;
            //if (rayosLanzados == rayoAnalizar) {
            //    verbose = true;
            //}
            
            Pixel devuelto = colorPath(primitivas, rayo, verbose);

            recibidos.push_back(devuelto);
            //rayosLanzados++;
        }

        imagen.imageMatrix[miraPixel]=media(recibidos);

        if (miraPixel % 10000 == 0){
            cout << "\r" << "Calculados " << (float)miraPixel*100/totalPixeles << " % de pixeles     ";
        }
    }
    cout << "\r" << "Calculados " << "100" << " % de pixeles     " << endl;
    return imagen;
}