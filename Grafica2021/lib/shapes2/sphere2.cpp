#pragma once

#include "sphere2.hpp"

sphere::sphere(){
}

sphere::sphere(vec3 center_, float radius_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor){
    this->center=center_;
    this->radius=radius_;
    this->color=color_;
    this->diffuse=_diffuse;
    this->reflective=_reflective;
    this->refractive=_refractive;
    this->refractIndex=_refractIndex;
    this->emisor=_emisor;
}

vec3 sphere::getCenter(){
    return this->center;
}

float sphere::getRadius(){
    return this->radius;
}

float sphere::getDiffuse(){
    return this->diffuse;
}

float sphere::getReflective(){
    return this->reflective;
}

float sphere::getRefractive(){
    return this->refractive;
}

bool sphere::getEmisor(){
    return this->emisor;
}

//https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
bool sphere::ray_intersect(ray r, colour& tono, float& distancia, vec3& normalParam) const{

    
    /*
    vec3 d = (r.direccion);
    vec3 d2 = normalizar(d);
    vec3 o = (r.origen);
    vec3 oc =(this->center);
    vec3 oc2 = (o-oc);

    float a = dot(d, d);
    float b = 2.0*dot(oc2, d);
    float c = dot(oc2, oc2) - (this->radius * this->radius);
    float discriminant = (b * b) - (4.0*(a * c));
    vec3 dondeGolpea;// = desplazarPunto(o, d);
    vec3 normalGolpe;
    if (discriminant >= 0) {
        float temp = (-(b + sqrt(discriminant)) / 2.0*a);
        float temp2 = (-(b - sqrt(discriminant)) / 2.0*a);
            
        tono = this->color;

        if ((temp) < (temp2)) {
            distancia = (temp);
            vec3 aux = d2 * distancia;
            dondeGolpea = desplazarPunto(o, aux);
            normalGolpe = vector2puntos(dondeGolpea, oc); 
            //normalGolpe = vector2puntos(oc, dondeGolpea);
        }else{
            distancia = (temp2);
            vec3 aux = d2 * distancia;
            dondeGolpea = desplazarPunto(o, aux);  
            normalGolpe = vector2puntos(dondeGolpea, oc);
            //normalGolpe = vector2puntos(oc, dondeGolpea);  
        }
        //vec3 normalGolpe = vector2puntos(centro, dondeGolpea);     //Vector resultante de origen - golpe
        normalParam = normalGolpe;
        normalParam = normalizar(normalGolpe);
        return true;
    } 
    return false;
*/

/*
    vec3 oc = r.origen - this->center;
    vec3 rdir = normalizar(r.direccion);
    float a = dot(rdir, rdir);
    float b = 2*dot(oc, rdir);
    float c = dot(oc,oc) - this->radius*this->radius;
    float discriminant = b*b - 4*a*c;
    tono = this->color;
    if(discriminant < 0){
        return false;
    }
    else{

        float numerator = -b - 2*sqrt(discriminant);
        if (numerator >= 0.0) {
            distancia = numerator / (2*a);
             tono = this->color;
            vec3 dondeGolpea = desplazarPunto(r.origen, rdir, distancia);
            vec3 normalGolpe = vector2puntos( this->center, dondeGolpea ); //impacto - centro
            normalParam = normalizar(normalGolpe);
            return true;
        }

        numerator = -b + 2*sqrt(discriminant);
        if (numerator >= 0.0) {
             distancia = numerator / (2*a);
             tono = this->color;
            vec3 dondeGolpea = desplazarPunto(r.origen, rdir, distancia);
            vec3 normalGolpe = vector2puntos( this->center, dondeGolpea ); //impacto - centro
            normalParam = normalizar(normalGolpe);
            return true;
        }
        else {
            return false;
        }

    }
*/


//http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
    vec3 d = r.direccion;
    vec3 o = r.origen;
    vec3 c = this->center;
    float r2 = this->radius;

    float t1, t2;

    vec3 L = c-o;
    float tca = dot(L, d);
    if(tca < 0) return false;

    float d2 = dot(L,L) - tca * tca;
    if (d2 > r2 * r2) return false; 

    float thc = sqrt(r2*r2-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if (t1 < 0) return false;
    }

    tono = this->color;
    distancia = t1;
    vec3 dondeGolpea = o+(d)*(distancia);
    vec3 normalGolpe = dondeGolpea-(c);     //Vector resultante de origen - golpe
    normalParam = normalizar(normalGolpe);
    return true;


/*
    vec3 d = normalizar(r.direccion);
    vec3 l = r.direccion;
    vec3 o = r.origen;
    vec3 c = this->center;
    float r2 = this->radius;

    float t1, t2;

    vec3 L = l-(o);
    float tca = dot(L, d);

    if(tca < 0) return false;

    float d2 = dot(L,L) - tca * tca;

    if (d2 > r2 * r2) return false; 

    float thc = sqrt((r2*r2)-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if(t1 < 0){
            return false;
        }
    }

    tono = this->color;
    distancia = t1;
    vec3 dondeGolpea = o+(normalizar(d)*(distancia));
    vec3 normalGolpe = dondeGolpea-(c);     //Vector resultante de origen - golpe
    vec3 aux = d * distancia;
    dondeGolpea = desplazarPunto(o, aux);
    normalGolpe = vector2puntos(dondeGolpea, c); 
    normalParam = normalizar(normalGolpe);
    return true;
    */
   
   /*
   vec3 oc = r.origen - center;
   float a = dot(r.direccion, center);
   float b = 2.0* dot(oc, r.direccion);
   float c = dot(oc, oc) - radius*radius;
   float discriminant = b*b - 4.0*a*c;
   if (discriminant < 0 || a == 0){
       return false;
   }
   else {
       distancia = (-b - sqrt(discriminant)) / (2.0*a);
       vec3 aux = normalizar(r.direccion) * distancia;
       vec3 dondeGolpea = desplazarPunto(r.origen, aux);
       normalParam = vector2puntos(oc, dondeGolpea);
       tono = this->color;
       return true;
   }
   */
   
}

//http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
bool sphere::ray_intersect2(ray r, colour& tono, float& distancia, vec3& normalParam) const{

    vec3 d = r.direccion;
    vec3 o = r.origen;
    vec3 c = this->center;
    float r2 = this->radius;

    float t1, t2;

    vec3 L = c-o;
    float tca = dot(L, d);
    if(tca < 0) return false;

    float d2 = dot(L,L) - tca * tca;
    if (d2 > r2 * r2) return false; 

    float thc = sqrt(r2*r2-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if (t1 < 0) return false;
    }

    tono = this->color;
    distancia = t2;
    vec3 dondeGolpea = o+(d)*(distancia);
    vec3 normalGolpe = dondeGolpea-(c);     //Vector resultante de origen - golpe
    normalParam = normalizar(normalGolpe);
    return true;   
}


string sphere::queSoy() const{
    return "esfera";
}

void sphere::material(float& Kd, float& Ks, float& Kr) const {
    Kd = this->diffuse;
    Ks = this->reflective;
    Kr = this->refractive;
}

bool sphere::getEmisor() const {
    return emisor;
}

float sphere::getRIndex() const {
    return this->refractIndex;
}