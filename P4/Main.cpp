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
    PHONG_DIFFUSE,
    PHONG_SPECULAR,
    DEAD
};

EVENT getRandomEvent(const Material &material, const Vectores &position) {
    // Russian roulette

    // get percentages based on the max value of each color
    float maxKd = getColor(material.reflectance.kd, position).max();
    float maxKs = getColor(material.reflectance.ks, position).max();
    float maxKdPhong = getColor(material.reflectance.kdPhong, position).max();
    float maxKsPhong = getColor(material.reflectance.ksPhong, position).max();

    // cap to max value
    const float MAX = 0.99f;
    float sum = maxKd + maxKs + maxKdPhong + maxKsPhong;
    if (sum > MAX) {
        maxKd *= MAX / sum;
        maxKs *= MAX / sum;
        maxKdPhong *= MAX / sum;
        maxKsPhong *= MAX / sum;
    }

    float randomZeroToOne = random_cero_to_uno();
    if ((randomZeroToOne -= maxKd) < 0) {
        // Perfect refraction case (delta BTDF)
        return REFRACTION;
    } else if ((randomZeroToOne -= maxKs) < 0) {
        // Perfect specular reflectance case (delta BRDF)
        return REFLECTION;
    } else if ((randomZeroToOne -= maxKdPhong) < 0) {
        // Perfect Phong case (Phong BRDF)
        return PHONG_DIFFUSE;
    } else if ((randomZeroToOne -= maxKsPhong) < 0) {
        // Perfect Phong case (Phong BRDF)
        return PHONG_SPECULAR;
    } else {
        // Path deaths
        return DEAD;
    }
}

/*
Vectores reflect(Vectores &in, Vectores &n) {
    return (in - n * in.punto(n) * 2.0f).normalizar();
}

Vectores refract(Vectores &in, Vectores n, stack<const Object *> &refractionStack,
               float sceneRefractiveIndex, const Object *object) {
    float c = -dot(n, in), refractionRatio;

    refractionRatio = sceneRefractiveIndex / object->refractiveIndex;

    if (c < 0) {
        // the normal and the ray have the same direction
        refractionRatio = 1.0f / refractionRatio;
        c = -c;
        n = -n;
    }
    float radicand = 1.0f - refractionRatio * refractionRatio * (1.0f - c * c);
    if (radicand < 0.0f) {
        return reflect(in, n);
    } else {
        return norm(in * refractionRatio + n * (refractionRatio * c - sqrt(radicand)));
    }
}*/


Vectores nuevaDireccion(EVENT event, Vectores position, Vectores direction,string objeto, Vectores objetoV ,stack<const Object *> &refractionStack, float sceneRefractiveIndex){ //objeto será esfera o plano, y su vector o el centro (esfera) o la normal del plano
    Vectores n;
    if (objeto == "esfera"){
        n = position.restarVector(objetoV).normalizar();
    }else{ //plano
        n = objetoV.normalizar();
    }
    switch (event) {
        case REFRACTION:
            return refract(direction, n, refractionStack, sceneRefractiveIndex, &object);
        case REFLECTION:
            return reflect(direction, n);
        case PHONG_DIFFUSE: {
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
        case PHONG_SPECULAR: {
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
             
            float theta = acos(pow(random_cero_to_uno(), (1.0f / (object.material.property.reflectance.s + 1.0f))));
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
        Material materialGolpeado;
        Material materialFinal;

        for (auto obstacle : entorno){          //Calcula con que obstaculo golpea
            if(obstacle->ray_intersect(ray,visto,distancia, materialGolpeado)){ 
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
        }else {  //Ha impactado con algun objeto:     p = o + rayo * distnacia
            Vectores nuevoOrigen;
            nuevoOrigen = nuevoOrigen.calculaPunto(ray.origen, ray.direccion, menorDistancia);

            EVENT eventoActual = getRandomEvent(materialFinal, nuevoOrigen);

            //Calcular color y actualizar BRDF
            pixelaux.multiplicaTotal(BRDF);
             if (eventoActual == PHONG_DIFFUSE || eventoActual == PHONG_SPECULAR) {

             }
                    /*
                    if (event == PHONG_DIFFUSE || event == PHONG_SPECULAR) {
                        for (const LightPoint &lightPoint : scene.lightPoints) {
                            // foreach light
                            if (isLightVisible(lightPoint, position, scene.objects)) {

                                // if visible, compute path light
                                HCoord lightVect = position - lightPoint.position;
                                float lightDist = mod(lightVect);
                                Color direct = lightPoint.color
                                               * getBRDF(event, norm(lightVect), -direction, position, *intersection)
                                               * rayFactor
                                               / (lightDist * lightDist);

                                directTotal = directTotal + direct;
                            }
                        }
                    }*/
            //Calcular nueva direccion de rebote:
                //TODO GENERAR DIRECCION

            //Actualizar rayo
                //TODO actualizar direccion
            ray.origen = nuevoOrigen;

            rebotes++;  //Mira a ver si es el último rebote
            if (eventoActual == DEAD){
                impactado = true;
                sigueRebotando = false;
            }
        }
                
    if (BRDF <= 0.0){   //Si se ha quedado sin luz el rayo
        impactado = false;
        sigueRebotando = false;
    }

    pixelResultado.divideTotal(rebotes); 
    return pixelResultado;
}



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
