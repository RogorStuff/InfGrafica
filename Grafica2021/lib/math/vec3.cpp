#pragma once

#include "vec3.hpp"

vec3::vec3(){}

vec3::vec3(float x_, float y_, float z_, int punto_){
    x=x_;
    y=y_;
    z=z_;
    punto=punto_;
}

float vec3::modulo(){
    return sqrt(this->x*this->x+this->y*this->y+this->z*this->z);
}

float dot(vec3 a, vec3 b){
    return (a.x*b.x+a.y*b.y+a.z*b.z);
}

vec3 cross(vec3& a, vec3& b){
    return vec3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x, 0);
}

vec3 desplazarPunto(vec3& punto, vec3& direccion){
    return vec3(punto.x+direccion.x, punto.y+direccion.y, punto.z+direccion.z, 1);
}

vec3 desplazarPunto(vec3& punto, vec3& direccion, float distancia){
    return vec3(punto.x+direccion.x*distancia, punto.y+direccion.y*distancia, punto.z+direccion.z*distancia, 1);
}

vec3 vector2puntos(vec3& punto1, vec3& punto2){
    return vec3(punto2.x-punto1.x, punto2.y-punto1.y, punto2.z-punto1.z, 0);
}

vec3 normalizarPunto(vec3& punto){
    return vec3(punto.x/punto.punto, punto.y/punto.punto, punto.z/punto.punto, punto.punto/punto.punto);
}

vec3 normalizar(vec3& punto){
    
    float mod = punto.modulo();
    float Ax = punto.x/mod;
    float Ay = punto.y/mod;
    float Az = punto.z/mod;
    return vec3(Ax, Ay, Az, punto.punto);
}

vec3 negado(vec3 vector){
    vec3 aux;
    aux.x = -vector.x;
    aux.y = -vector.y;
    aux.z = -vector.z;
    aux.punto = vector.punto;
    return aux;
}

vec3 ProductoVectorial(vec3 p1, vec3 p2){
    vec3 aux (p1.y*p2.z - p1.z*p2.y, p1.z*p2.x - p1.x*p2.z, p1.x*p2.y - p1.y*p2.x, 0);
    return aux;
}

vec3 vec3::operator+(const vec3& b){
    return vec3(this->x+b.x, this->y+b.y, this->z+b.z, this->punto);
}
vec3 vec3::operator-(const vec3& b){
    return vec3(this->x-b.x, this->y-b.y, this->z-b.z, this->punto);
}
vec3 vec3::operator*(const float& b){
    return vec3(this->x*b, this->y*b, this->z*b, this->punto);
}
vec3 vec3::operator/(const float& b){
    if (b != 0){
        return vec3(this->x/b, this->y/b, this->z/b, this->punto);
    }
    //Error, vector nulo
    return vec3();
}


ostream& operator<<(ostream& os, const vec3& vec)
{
    os << "x: "<< vec.x << "| y: " << vec.y << "| z: " << vec.z;
    return os;
}