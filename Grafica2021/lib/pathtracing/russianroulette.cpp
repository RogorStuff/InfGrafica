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
    const float MAX = 0.95f;
    float sum = Kd + Ks + Kr;
    //if (sum > MAX) {
        Kd *= MAX / sum;
        Ks *= MAX / sum;
        Kr *= MAX / sum;
    //}

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    float randomZTO = dist(mt); //((double) rand() / (RAND_MAX));

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
        return refraction(entra, normal, puntoChoque, obstaculo);
        break;

    case DEAD:
        return vec3(0.0, 0.0, 0.0, 0);      //Vector nulo
        break;
        
    default:
        return vec3(0.0, 0.0, 0.0, 0);      //Vector nulo
        break;
    }
}


vec3 diffuse(vec3 in, vec3 n, vec3 choque){
    //eo = rand_f(0,1);
    float theta = acos(sqrt(((double) rand() / (RAND_MAX))));   //Inclinacion
    float p = 2.0 * M_PI * ((double) rand() / (RAND_MAX));      //Azimuth

    vec3 resultado = vec3((sin(theta)*cos(p)), (sin(theta)*sin(p)), cos(theta), 0); 

    vec3 z = n;
    z = normalizarPunto(z);

    vec3 aux = vec3(n.x+24, n.y+48 , n.z, 0);
    //vec3 aux = n;
    //aux.normalizar();
    vec3 y = ProductoVectorial(z, aux);
    y = normalizarPunto(y);

    vec3 x = ProductoVectorial(z, y);
    x = normalizarPunto(x);

    vec3 choque_ = choque;

    //Matrix4x4 matrizCambioBase = Matrix4x4(x.c[0],x.c[1],x.c[2],x.tipoPunto,y.c[0],y.c[1],y.c[2], y.tipoPunto,z.c[0],z.c[1],z.c[2], z.tipoPunto,choque_.c[0],choque_.c[1],choque_.c[2], choque_.tipoPunto);
    matrix matrizCambioBase = matrix(x, y, z, choque);
    resultado = translation(matrizCambioBase, resultado);

    resultado = normalizarPunto(resultado);
    return resultado;
}