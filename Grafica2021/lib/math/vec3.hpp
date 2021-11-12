#pragma once

#include <math.h> 
#include <fstream>
#include <string> 
#include <iostream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

class vec3{

    public:
        float x;
        float y;
        float z;

        int punto;

        vec3();
        vec3(float x_, float y_, float z_, int punto_);

        float modulo();
        //float dot(vec3& a, vec3& b);
        //vec3 cross(vec3& a, vec3& b);
        //vec3 desplazarPunto(vec3& punto, vec3& direccion);
        //vec3 vector2puntos(vec3& punto1, vec3& punto2);
        //vec3 normalizarPunto(vec3& punto);
        vec3 operator+(const vec3& b);
        vec3 operator-(const vec3& b);
        vec3 operator-()const;
        vec3 operator*(const float& b);
        vec3 operator/(const float& b);
        
};