#pragma once

#include "plane2.hpp"

plane::plane(){
}

plane::plane(vec3 center_,vec3 normal_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor, vec3 supizq_ = vec3(0, 0, 0, 0), vec3 infder_ = vec3(0, 0, 0, 0)){
    this->center=center_;
    this->normal=normal_;
    this->color=color_;
    this->diffuse=_diffuse;
    this->reflective=_reflective;
    this->refractive=_refractive;
    this->refractIndex=_refractIndex;
    this->emisor=_emisor;

    if (this->center.x == -10){ //izq
        this->infder = vec3(-10,-10,-40,0);
        this->supizq = vec3(-10,10,30,0);
        
    } else if (this->center.x == 10){   //der
        this->infder = vec3(10,-10,-40,0);
        this->supizq = vec3(10,10,30,0);

    } else if (this->center.y == -10){  //suelo
        this->infder = vec3(-10,-10,-40,0);
        this->supizq = vec3(10,-10,30,0);
        
    } else if (this->center.y == 10){   //techo
        this->infder = vec3(-10,10,-40,0);
        this->supizq = vec3(10,10,30,0);

    } else if (this->center.z == 30){   //Fondo
        this->infder = vec3(-10,-10,30,0);
        this->supizq = vec3(10,10,30,0);

    } else {
        std::cout << "Plano no reconocido de limites " << std::endl;
        this->infder = vec3(0, 0, 0, 0);
        this->supizq = vec3(0, 0, 0, 0);
    }

}

vec3 plane::getCenter(){
    return this->center;
}

vec3 plane::getNormal(){
    return this->normal;
}

float plane::getDiffuse(){
    return this->diffuse;
}

float plane::getReflective(){
    return this->reflective;
}

float plane::getRefractive(){
    return this->refractive;
}

bool plane::getEmisor(){
    return this->emisor;
}


bool plane::ray_intersect(ray rayo, colour& tono, float& distancia, vec3& normalParam) const{

    vec3 l = rayo.direccion;
    vec3 po = this->center;
    vec3 lo = rayo.origen;
    vec3 n = this->normal;
    vec3 nNegado = negado(n);

    bool ret = false;
    float dist = 0.0;

    float denominator = dot(l, n);
    float denominator2 = dot(l, nNegado);

    if (denominator != 0.0) {
        vec3 aux = po-lo;
        dist = dot(aux, n) / denominator;
        if (dist > 0) {
            distancia = dist;
            tono = this->color;
            normalParam = n;
            vec3 puntoChoque = desplazarPunto(rayo.origen, rayo.direccion, distancia);
            
            //if ((puntoChoque.x> supizq.x && puntoChoque.x< infder.x) || (puntoChoque.x< supizq.x && puntoChoque.x> infder.x) || (supizq.x == infder.x)) {
            //    if ((puntoChoque.y> supizq.y && puntoChoque.y< infder.y) || (puntoChoque.y< supizq.y && puntoChoque.y> infder.y) || (supizq.y == infder.y)) {
            //        if ((puntoChoque.z> supizq.z && puntoChoque.z< infder.z) || (puntoChoque.z< supizq.z && puntoChoque.z> infder.z) || (supizq.z == infder.z)) {
            /*if ( (puntoChoque.x< supizq.x && puntoChoque.x> infder.x) || (supizq.x == infder.x)) {
                if ( (puntoChoque.y< supizq.y && puntoChoque.y> infder.y) || (supizq.y == infder.y)) {
                    if ( (puntoChoque.z< supizq.z && puntoChoque.z> infder.z) || (supizq.z == infder.z)) {
                        ret= true;
                    } else {
                        ret = false;
                    }   
                } else {
                    ret = false;
                }
            } else {
                ret = false;
            }*/
            ret = true;
        }
    } else if (denominator2 != 0.0) {
        vec3 aux = po-lo;
        dist = dot(aux, nNegado) / denominator2;
        if (dist > 0) {
            distancia = dist;
            tono = this->color;
            normalParam = n;
            vec3 puntoChoque = desplazarPunto(rayo.origen, rayo.direccion, distancia);
            /*if ( (puntoChoque.x< supizq.x && puntoChoque.x> infder.x) || (supizq.x == infder.x)) {
                if ( (puntoChoque.y< supizq.y && puntoChoque.y> infder.y) || (supizq.y == infder.y)) {
                    if ( (puntoChoque.z< supizq.z && puntoChoque.z> infder.z) || (supizq.z == infder.z)) {
                        ret= true;
                    } else {
                        ret = false;
                    }   
                } else {
                    ret = false;
                }
            } else {
                ret = false;
            }*/
            ret = true;
        }
    }
    return ret;


    /*
    //https://stackoverflow.com/questions/23975555/how-to-do-ray-plane-intersection
    // Crashea al generar la imagne, parece que es bucle infinito
    vec3 esteCentro = this->center;
    vec3 estaNormal = this->normal;
    float denom = dot(estaNormal, rayo.direccion);
    if (fabs(denom) > 0){
        vec3 polo = vector2puntos(rayo.origen, esteCentro);
        float t = dot(estaNormal, esteCentro);
        if (t > 0){
            distancia = t ;
            tono = this->color;
            normalParam = this->normal;
            return true;
        }else{
            return false;
        }
    }
    return false;
    */
/*
    https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
   float tmin, tmax, tymin, tymax, tzmin, tzmax; 

 
    tmin = (bounds[r.sign[0]].x - rayo.origen.x) * r.invdir.x; 
    tmax = (bounds[1-r.sign[0]].x - rayo.origen.x) * r.invdir.x; 
    tymin = (bounds[r.sign[1]].y - rayo.origen.y) * r.invdir.y; 
    tymax = (bounds[1-r.sign[1]].y - rayo.origen.y) * r.invdir.y; 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 
 
    tzmin = (bounds[r.sign[2]].z - rayo.origen.z) * r.invdir.z; 
    tzmax = (bounds[1-r.sign[2]].z - rayo.origen.z) * r.invdir.z; 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
    if (tzmin > tmin) 
        tmin = tzmin; 
    if (tzmax < tmax) 
        tmax = tzmax;  
 
    return true; 
*/

}



bool plane::ray_intersect2(ray rayo, colour& tono, float& distancia, vec3& normalParam) const{

    return false;
}


string plane::queSoy() const{
    return "plano";
}

void plane::material(float& Kd, float& Ks, float& Kr) const {
    Kd = this->diffuse;
    Ks = this->reflective;
    Kr = this->refractive;
}

bool plane::getEmisor() const {
    return emisor;
}

float plane::getRIndex() const {
    return this->refractIndex;
}