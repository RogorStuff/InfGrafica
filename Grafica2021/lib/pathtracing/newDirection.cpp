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


vec3 diffuse(vec3 in, vec3 n, vec3 choque){
    //eo = rand_f(0,1);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    float theta = acos(sqrt(dist(mt)));   //Inclinacion
    float p = 2.0 * M_PI * (dist(mt));      //Azimuth

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

vec3 reflect(vec3 in, vec3 n) { //n is the normal of the surface (mirror), in is the received vector
    vec3 aux = n*(dot(in, n));
    aux*(2.0);
    vec3 resultado = aux-in;
    resultado = normalizarPunto(resultado);
    return resultado;
}


vec3 refract(vec3 in, vec3 n, vec3 choque, Primitiva* obstaculo){

    float refraccionExterior = 1.0003F;
    float refraccionObject = obstaculo->getRIndex();

    float mu = refraccionExterior/(refraccionObject+0.01);

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