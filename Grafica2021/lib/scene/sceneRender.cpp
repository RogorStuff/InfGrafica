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

Pixel colorPathR(vector<Primitiva*> &primitivas, ray rayoLanzado, bool& noGolpea, int loop){
    colour visto = colour(0.0, 0.0, 0.0);
    float distanciaGolpe;
    float menorDistancia = INFINITY;
    Pixel resultado;
    noGolpea = true;
    vec3 vectorNormal;
    Primitiva* objetoGolpeado;
    for (Primitiva* p : primitivas){

        if (p->ray_intersect(rayoLanzado, visto, distanciaGolpe, vectorNormal)){
            noGolpea = false;
            if (distanciaGolpe < menorDistancia){
                resultado.update(visto);
                menorDistancia=distanciaGolpe;
                objetoGolpeado = p;
            }
        }
    }

    if (!noGolpea){
        if (objetoGolpeado->getEmisor()){
            //cout<<"Emisor"<<endl;
            //std::cout << "Rayo golpea con emisor" << std::endl;
            //float kd, ks, ktuputamadre;
            //objetoGolpeado->material(kd, ks, ktuputamadre);
            //std::cout << "El emisor golpea tla que " << kd << std::endl;
            return resultado;
        } else {    //Objeto golpeado no emisor
            bool golpeAux;
            EVENT eventoObjeto;
            if(loop<4){
                eventoObjeto = getRandomEvent2(objetoGolpeado);
                while (eventoObjeto == DEAD){
                    eventoObjeto = getRandomEvent2(objetoGolpeado);
                }
            }else{
                eventoObjeto = getRandomEvent(objetoGolpeado);
            }
            if (eventoObjeto != DEAD){
                vec3 puntoChoque = desplazarPunto(rayoLanzado.origen, rayoLanzado.direccion, menorDistancia);
                //cout<<"Antiguo centro: "<<rayoLanzado.origen<<" y antigua direccion "<<rayoLanzado.direccion<<" con distancia "<<distanciaGolpe <<" en iteracion "<<loop<<endl;
                //cout << "Loop: "<< loop << endl;
                vec3 newDirectionRay = generarDireccion(eventoObjeto, rayoLanzado.direccion, vectorNormal, puntoChoque, objetoGolpeado);
                //cout<<"Nuevo direccion: "<<newDirectionRay<<endl;
                //newDirectionRay = normalizar(newDirectionRay);  //Esto aclara, puede que no deba estar
                //newDirectionRay = translation(cameraToWorld, newDirectionRay);
                ray nuevoRayo = ray(puntoChoque, newDirectionRay);
                if (eventoObjeto == REFLECTION){
                    //cout<<"Nuevo origen: "<<puntoChoque<<" y nueva direccion "<<newDirectionRay<<endl;
                    return (colorPathR(primitivas, nuevoRayo, golpeAux,0));
                }else{
                    if(loop==2){
                        //resultado = Pixel(0.0, 0.0, 0.0);
                    }
                    return (resultado * colorPathR(primitivas, nuevoRayo, golpeAux, loop+1));
                }
            }else{
                //std::cout << "Rayo muere en ruleta" << std::endl;
                return Pixel(0.0, 0.0, 0.0);
            }
        }
    }
    else {
        //std::cout << "Rayo no golpea con nada" << std::endl;
    }
    return resultado;
}




Pixel colorPath(vector<Primitiva*> &primitivas, ray rayoLanzado, bool& noGolpea){
    colour visto = colour(0.0, 0.0, 0.0);
    float distanciaGolpe;
    float menorDistancia = INFINITY;
    Pixel resultado;
    noGolpea = true;
    vec3 vectorNormal;
    Primitiva* objetoGolpeado;
    for (Primitiva* p : primitivas){

        if (p->ray_intersect(rayoLanzado, visto, distanciaGolpe, vectorNormal)){
            noGolpea = false;
            if (distanciaGolpe < menorDistancia){
                resultado.update(visto);
                menorDistancia=distanciaGolpe;
                objetoGolpeado = p;
            }
        }
    }

    if (!noGolpea){
        if (objetoGolpeado->getEmisor()){
            //cout<<"Emisor"<<endl;
            return resultado;
        } else {    //Objeto golpeado no emisor
            bool golpeAux;
            EVENT eventoObjeto = getRandomEvent(objetoGolpeado);
            if (eventoObjeto != DEAD){
                vec3 puntoChoque = desplazarPunto(rayoLanzado.origen, rayoLanzado.direccion, menorDistancia);
                //cout<<"Antiguo centro: "<<rayoLanzado.origen<<" y antigua direccion "<<rayoLanzado.direccion<<" con distancia "<<distanciaGolpe <<endl;
                //cout<<"Nuevo centro: "<<puntoChoque<<endl;
                vec3 newDirectionRay = generarDireccion(eventoObjeto, rayoLanzado.direccion, vectorNormal, puntoChoque, objetoGolpeado);
                //newDirectionRay = normalizar(newDirectionRay);  //Esto aclara, puede que no deba estar
                //newDirectionRay = translation(cameraToWorld, newDirectionRay);
                ray nuevoRayo = ray(puntoChoque, newDirectionRay);
                //cout<<"Nuevo origen: "<<puntoChoque<<" y nueva direccion "<<newDirectionRay<<endl;
                if (eventoObjeto == REFLECTION){
                    return (colorPathR(primitivas, nuevoRayo, golpeAux, 1));
                }else{
                    // resultado = Pixel(0.0, 0.0, 0.0);
                    return (resultado * colorPathR(primitivas, nuevoRayo, golpeAux, 1));
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

        for (int i=0; i<numRayos; i++){

            // Tomamos un punto del pixel dejando un margen de 5% por cada lado
            float X = (float)(dist(mt))/100;
            float Y = (float)(dist(mt))/100;
            // Ponemos las coordenadas en la esquina superior izquierda y desplazamos dentro de dicho margen
            vec3 rayDirection(x+X/(float)anchototal, y+Y/(float)altoTotal, sensor.apunta.z, 0);
            // Generar rayo
            //rayDirection = translation(cameraToWorld, rayDirection);
            ray rayoAux(sensor.coordenadasO,rayDirection);
            // Añadimos rayo al conjunto total
            rayos.push_back(rayoAux);
        }

        vector<Pixel> recibidos;    //Tenemos todos los rayos, empezamos a mirar que color devuelve cada rayo
        for (ray rayo : rayos){

            bool noGolpeado;
            Pixel devuelto = colorPath(primitivas, rayo, noGolpeado);

            //if(!noGolpeado){
                recibidos.push_back(devuelto);            //TODO CUIDADO QUE IGUAL ES REFERENCIA Y PASA TODO A 0 0 0
            //}
        }

        
        imagen.imageMatrix[miraPixel]=media(recibidos);
        
        //cout<<"No impacta";
        

        if (miraPixel % 1000 == 0){
            cout << "\r" << "Calculados " << (float)miraPixel*100/totalPixeles << " % de pixeles";
        }
    }
    cout << "\r" << "Calculados " << "100" << " % de pixeles" << endl;
    return imagen;
}