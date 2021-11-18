#pragma once

#include "../math/vec3.cpp"
#include "../math/matrix.cpp"
#include "../scene/ray.cpp"
#include "../shapes2/primitiva.hpp"
#include "../shapes2/sphere2.cpp"
#include "../shapes2/plane2.cpp"

#include <cmath>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;
# define M_PI           3.14159265358979323846

enum EVENT {
    DIFFUSE,
    REFRACTION,
    REFLECTION,
    DEAD            
};


EVENT getRandomEvent(Primitiva* primitiva) {
    // Russian roulette
    
    float Kd;
    float Ks;
    float Kr;
    
    primitiva->material(Kd, Ks, Kr);

    // Max value limit
    const float MAX = 0.9;
    float sum = Kd + Ks + Kr;
    if (sum > MAX) {
        Kd *= MAX / sum;
        Ks *= MAX / sum;
        Kr *= MAX / sum;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    float randomZTO = (float)(rand() % 100)/100.0; //((double) rand() / (RAND_MAX));

    if ((randomZTO -= Kd) < 0) {
        // DIFFUSE case
        return DIFFUSE;
    } else if ((randomZTO -= Ks) < 0) {
        // SPECULAR case 
        return REFLECTION;
    } else if ((randomZTO -= Kr) < 0) {
        // REFRACTION case
        return REFRACTION;
    } else {
        // DEAD case
        return DEAD;
    }
}

EVENT getRandomEvent2(Primitiva* primitiva) {
    // Russian roulette
    
    float Kd;
    float Ks;
    float Kr;
    
    primitiva->material(Kd, Ks, Kr);

    // Max value limit
    const float MAX = 1.0;
    float sum = Kd + Ks + Kr;
    //if (sum > MAX) {
        Kd *= MAX / sum;
        Ks *= MAX / sum;
        Kr *= MAX / sum;
    //}

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    float randomZTO = (float)(rand() % 100)/100.0; //((double) rand() / (RAND_MAX));

    if ((randomZTO -= Kd) < 0) {
        // DIFFUSE case
        return DIFFUSE;
    } else if ((randomZTO -= Ks) < 0) {
        // SPECULAR case 
        return REFLECTION;
    } else if ((randomZTO -= Kr) < 0) {
        // REFRACTION case
        return REFRACTION;
    }
    return DEAD;
}

vec3 diffuse(vec3 in, vec3 n, vec3 choque){
/*
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);


    float theta = acos(sqrt((float)(rand() % 100)/100.0));   //Inclinacion
    float p = 2.0 * M_PI * ((float)(rand() % 100)/100.0);      //Azimuth

    vec3 resultado = vec3((sin(theta)*cos(p)), (sin(theta)*sin(p)), cos(theta), 0); 
    vec3 z = n;
    z = normalizar(z);

    vec3 x = cross(in, z);
    x = normalizar(x);

    vec3 y = cross(x, z);
    y = normalizar(y);
    
    matrix matrizCambioBase = matrix(x, y, z, choque);
    resultado = baseChange(matrizCambioBase, resultado);

    resultado = normalizar(resultado);

    return resultado;
*/

    float r1 = 2*M_PI*((float)(rand() % 100)/100.0);
    float r2 = (float)(rand() % 100)/100.0;
    float r2s = sqrt(r2);
    vec3 w = n;
    vec3 u = (cross(fabs(w.x) >.1?vec3(0, 1, 0, 0):vec3(1, 0, 0, 0),w));
    vec3 v = cross(w, u);
    vec3 d = normalizar(u * cos(r1) * r2s + v*sin(r1)*r2s + w*sqrt(1-r2));

    return d;
    
}

vec3 reflect(vec3 in, vec3 n) { //n is the normal of the surface (mirror), in is the received vector
    vec3 resultado = in-(n*dot(in,n)*2.0);
    resultado = normalizar(resultado);
    return resultado;
}


vec3 refract(vec3 in, vec3 n, vec3 choque, Primitiva* obstaculo){

    float refraccionExterior = 1.001;
    float refraccionObject = obstaculo->getRIndex();

    float mu = refraccionExterior/(refraccionObject+0.001);

    vec3 normal = n;
    vec3 externa = in;
    float cosExterior = - dot(externa,normal);
    float k = 1.0 - mu*mu * (1- cosExterior*cosExterior);

    vec3 interior;
    if(k<0){
        interior = externa;
    }else{
        interior = (externa*mu)+(normal*(mu*cosExterior-sqrt(k)));
    }

    //SegundaInteraccion

    ray rayoInterno = ray (choque, interior);
    float distanciaAux;
    vec3 normalGolpe;
    //obstaculo->ray_intersect(rayoInterno, emisorAux, distanciaAux, materialAux, normalGolpe); 

    normal = normalGolpe;
    externa = rayoInterno.direccion;
    cosExterior = - dot(externa, normal);
    k = 1.0 - mu * mu * (1- cosExterior*cosExterior);
    
    vec3 resultado;
    if(k<0){
        resultado = cross(normal, externa);
    }
    else{
        resultado = (externa*(mu))+(normal*(mu*cosExterior-sqrt(k)));
    }

    return resultado;
} 

vec3 generarDireccion(EVENT e, vec3 entra, vec3 normal, vec3 puntoChoque, Primitiva* obstaculo){
    switch (e)
    {
    case DIFFUSE:
        return diffuse(entra, normal, puntoChoque);
        break;

    case REFLECTION:
        return reflect(entra, normal);
        break;

    case REFRACTION:
        return refract(entra, normal, puntoChoque, obstaculo);
        break;

    case DEAD:
        return vec3(0.0, 0.0, 0.0, 0);      //Vector nulo
        break;
        
    default:
        return vec3(0.0, 0.0, 0.0, 0);      //Vector nulo
        break;
    }
}