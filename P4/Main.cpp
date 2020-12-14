#include "emission.hpp"
#include "image.hpp"
#include "pixel.hpp"
#include "sensor.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "material.hpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include <time.h>

using namespace std;

float random_cero_to_uno(){
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

enum EVENT {
    REFRACTION,
    REFLECTION,
    DIFFUSE,
    SPECULAR,
    DEAD
};

EVENT getRandomEvent(const Material &material) {
    // Russian roulette

    float Kd = material.reflectance.kd;
    float Ks = material.reflectance.ks;
    float kdDiffuse = material.reflectance.kdDiffuse;
    float ksDiffuse = material.reflectance.ksDiffuse;

    // cap to max value
    const float MAX = 0.99f;
    float sum = Kd + Ks + kdDiffuse + ksDiffuse;
    if (sum > MAX) {
        Kd *= MAX / sum;
        Ks *= MAX / sum;
        kdDiffuse *= MAX / sum;
        ksDiffuse *= MAX / sum;
    }

    float randomZeroToOne = random_cero_to_uno();
    if ((randomZeroToOne -= Kd) < 0) {
        // Perfect refraction case (delta BTDF)
        return REFRACTION;
    } else if ((randomZeroToOne -= Ks) < 0) {
        // Perfect specular reflectance case (delta BRDF)
        return REFLECTION;
    } else if ((randomZeroToOne -= kdDiffuse) < 0) {
        // Diffuse case 
        return DIFFUSE;
    } else if ((randomZeroToOne -= ksDiffuse) < 0) {
        // Specular case
        return SPECULAR;
    } else {
        // Path deaths
        return DEAD;
    }
}


Vectores reflect(Vectores &in, Vectores &n) { //n is the normal of the surface (mirror), in is the received vector
    Vectores aux = n.multiplicarValor(in.punto(n));
    aux.multiplicarValor(2.0);
    return (in.restarVector(aux)).normalizar();
}

Vectores refract(Vectores in, Vectores n, float obstacleRefractiveIndex) {
    float c = -(n.punto(in));
    float refractionRatio = 1.0f / obstacleRefractiveIndex;

    if (c < 0) {
        // the normal and the ray have the same direction
        refractionRatio = 1.0f / refractionRatio;
        c = -c;
        n = n.negado();
    }
    float radicand = 1.0f - refractionRatio * refractionRatio * (1.0f - c * c);
    if (radicand < 0.0f) {
        return reflect(in, n);
    } else {
        Vectores aux = in.multiplicarValor(refractionRatio);
        Vectores aux2 = n.multiplicarValor(refractionRatio * c - sqrt(radicand));
        aux.sumarVector(aux2);
        return aux.normalizar();
    }
}


Vectores nuevaDireccion(EVENT event, Vectores position, Vectores direction,string objeto, Vectores objetoV, float obstacleRefractiveIndex){ //objeto será esfera o plano, y su vector o el centro (esfera) o la normal del plano
    Vectores n;
    if (objeto == "esfera"){
        n = position.restarVector(objetoV).normalizar();
    }else{ //plano
        n = objetoV.normalizar();
    }
    switch (event) {
        case REFRACTION:
            return refract(direction, n, obstacleRefractiveIndex);
        case REFLECTION:
            return reflect(direction, n);
        case DIFFUSE: {
            Vectores Z;
            Vectores Y;
            Vectores X;

            if (direction.punto(n) < 0) {
                // good side
                Z = n;
            } else {
                // opposite side
                Z = n.negado();
            }
            Y = (Z.cruce(direction)).normalizar();
            X = (Y.cruce(Z)).normalizar();

            float theta = acos(sqrt(random_cero_to_uno()));
            float phi = 2.0f * (float) M_PI * random_cero_to_uno();

            Matrix4x4 matrizTransformation(X.c[0], Y.c[0], Z.c[0], position.c[0], 
                                           X.c[1], Y.c[1], Z.c[1], position.c[1],
                                           X.c[2], Y.c[2], Z.c[2], position.c[2],
                                           0.0, 0.0, 0.0, 1.0);

            Vectores aux(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta),0);
            aux.traspConMatriz(matrizTransformation);
            return aux.normalizar();
        }
        case SPECULAR: {
            Vectores ref = reflect(direction, n);

            Vectores Z;
            Vectores Y;
            Vectores X;

            if (direction.punto(n) < nearZero) {
                Z = direction;
                Y = n;
                X = Y.cruce(Z);
            } else {
                X = direction.cruce(ref).normalizar();
                Y = ref;
                Z = Y.cruce(X);
            }
            Matrix4x4 matrizTransformation(X.c[0], Y.c[0], Z.c[0], position.c[0], 
                                           X.c[1], Y.c[1], Z.c[1], position.c[1],
                                           X.c[2], Y.c[2], Z.c[2], position.c[2],
                                           0.0, 0.0, 0.0, 1.0);
             
            float theta = acos(random_cero_to_uno());
            float phi = 2.0f * (float) M_PI * random_cero_to_uno();

            Vectores aux(cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta),0);
            aux.traspConMatriz(matrizTransformation);
            return aux.normalizar();
        }
        case DEAD:
            return Vectores(0.0,0.0,0.0,2); //El 2 al final indica el final
    }
}



Pixel colorRayo(Ray ray, vector<Obstacle*> &entorno, bool& impactado){

    Pixel pixelResultado(1.0, 1.0, 1.0);    //En cada rebote, pixel = pixel + NuevoColor*BRDF
    Pixel BRDF (1.0, 1.0, 1.0);             //
    int rebotes = 0;
    bool sigueRebotando = true;
    Vectores origen = ray.origen;
//    float BRDF = 1.0;

    while (sigueRebotando){

        bool impactado = false;
        Emission visto;
        float distancia;
        Pixel pixelaux;
        Obstacle* obstaculoGolpeado;
        float menorDistancia=1000000.0;
        Material* materialGolpeado;
        Material* materialFinal;
        float refractive;

        for (auto obstacle : entorno){          //Calcula con que obstaculo golpea
            if(obstacle->ray_intersect(ray,visto,distancia, *materialGolpeado, refractive)){ 
                impactado = true;
                if(distancia<menorDistancia){
                    materialFinal = materialGolpeado;
                    obstaculoGolpeado = obstacle;
                    pixelaux.update(visto);
                    menorDistancia=distancia;
                }
            }
        }

        if (!impactado){    //Si no impacta con nada, termina
            pixelResultado.update(0.0, 0.0, 0.0);
            impactado = false;
            sigueRebotando = false;
        }

        else {  //Ha impactado con algun objeto:     p = o + rayo * distnacia

            if (materialFinal->type == EMITTER){  //Es una luz, conseguir color y devolver todo
                pixelResultado.multiplicaTotal(obstaculoGolpeado->getColor());
                sigueRebotando = false;
            }
            else {  //Era un objeto no luz, calcular color, preparar siguiente color, calcular dirección y seguir el loop
                EVENT eventoActual = getRandomEvent(*materialFinal);
                pixelResultado.multiplicaTotal(obstaculoGolpeado->getColor());

                Vectores nuevoOrigen;
                nuevoOrigen = nuevoOrigen.calculaPunto(ray.origen, ray.direccion, menorDistancia);
                ray.origen = nuevoOrigen;
                //Mirar el tema direcciones segun evento.

                rebotes++;  //Contador de
                if (eventoActual == DEAD){
                    impactado = true;
                    sigueRebotando = false;
                }
            }
        }

        if (BRDF.escero()){   //Si se ha quedado sin luz el rayo
            impactado = false;
            sigueRebotando = false;
        //    pixelResultado.update(0.0, 0.0, 0.0);
        }

    }        

    pixelResultado.divideTotal(rebotes); 
    return pixelResultado;
}



int main () {
    srand (time(NULL));
    /*
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
    */
}
