#pragma once

#include "vec3.cpp"
#include "matrix.cpp"
#include "iostream"


class planet {
    public:
        vec3 center, normal, ciudad, estacion;
        float inclination, azimuth;
        float radio;

        planet();
        planet(vec3 center_, vec3 normal_, vec3 ciudad_, float inclination_, float azimuth_);

        bool ray_intersect(vec3 estacion, vec3 direccion, planet destino);

};

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) 
{ 
    float discr = b * b - 4 * a * c; 
    if (discr < 0) return false; 
    else if (discr == 0) x0 = x1 = - 0.5 * b / a; 
    else { 
        float q = (b > 0) ? 
            -0.5 * (b + sqrt(discr)) : 
            -0.5 * (b - sqrt(discr)); 
        x0 = q / a; 
        x1 = c / q; 
    } 
    if (x0 > x1) std::swap(x0, x1); 
 
    return true; 
}

planet::planet() {}

planet::planet(vec3 center_, vec3 normal_, vec3 ciudad_, float inclination_, float azimuth_) {
    float radio_ = normal_.modulo() / 2;
    float radio_2 = vector2puntos(center_, ciudad_).modulo();

    if (abs(radio_ - radio_2) < 0.0001 ) {
        center = center_;
        normal = normal_;
        ciudad = ciudad_;
        radio = radio_;
        inclination = inclination_;
        azimuth = azimuth_;
    }
    else {
        std::cout << "Planeta creado erroneamente " << abs(radio_ - radio_2) <<  std::endl;
    }
}

bool ray_intersect(planet origen, planet destino){

    float t0, t1;
    vec3 L = vector2puntos(origen.center, destino.center); 
    vec3 direccion = vector2puntos(origen.estacion, destino.estacion); 
    float a = dot(direccion, direccion); 
    float b = 2 * dot(direccion, L); 
    float c = dot(L,L) - origen.radio*origen.radio; 
    if (!solveQuadratic(a, b, c, t0, t1)) return false; 


    if (t0 > t1) std::swap(t0, t1); 
 
    if (t0 < 0) { 
        t0 = t1; // if t0 is negative, let's use t1 instead 
        if (t0 < 0) return false; // both t0 and t1 are negative 
    } 
 
    //float distancia = t0; 

    //Vectores dondeGolpea = r2.origen.sumarVector(r2.direccion.multiplicarValor(distancia));

 
    return true; 
};