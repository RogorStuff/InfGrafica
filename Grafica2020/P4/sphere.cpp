#pragma once

#include "sphere.hpp"

Sphere::Sphere(){
}

Sphere::Sphere(Vectores Ncentro, float Nradio, Emission Nemision, Material Nmaterial, float NrefractiveIndex){
    center=Ncentro;
    radius=Nradio;
    emision=Nemision;
    material = Nmaterial;
    refractiveIndex = NrefractiveIndex;
}

// Funcion de https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
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

bool Sphere::ray_intersect(Ray& r2, Emission& emite, float& distancia, Material& material, Vectores &normalGolpe) const{

    float t0, t1; // solutions for t if the ray intersects 
    // geometric solution
    /*
    Vectores L = center.VectorDosPuntos(r2.origen); 
    float tca = L.punto(r2.direccion); 
    // if (tca < 0) return false;
    float d2 = L.punto(L) - tca * tca; 
    if (d2 > this->radius*this->radius) return false; 
    float thc = sqrt(this->radius*this->radius - d2); 
    t0 = tca - thc; 
    t1 = tca + thc; 
    //analytic solution
    */
    Vectores L = r2.origen.VectorDosPuntos(center); 
    float a = r2.direccion.punto(r2.direccion); 
    float b = 2 * r2.direccion.punto(L); 
    float c = L.punto(L) - this->radius*this->radius; 
    if (!solveQuadratic(a, b, c, t0, t1)) return false; 


    if (t0 > t1) std::swap(t0, t1); 
 
    if (t0 < 0) { 
        t0 = t1; // if t0 is negative, let's use t1 instead 
        if (t0 < 0) return false; // both t0 and t1 are negative 
    } 
 
    distancia = t0; 

    emite = this->emision;
    material = this->material;
    Vectores dondeGolpea = r2.origen.sumarVector(r2.direccion.multiplicarValor(distancia));
    Vectores centro = this->center;
    normalGolpe = dondeGolpea.restarVector(centro);     //Vector resultante de origen - golpe
    normalGolpe.normalizar();
 
    return true; 
/*
*/ 

    
    //cout << "Entra en inserseccion de esfera" << endl;
    /*
    Vectores d = r2.direccion;
    Vectores o = r2.origen;

    Vectores oc = this->center;

    float t_min = -1;
    float t_max = 999999999999999;

    float a = d.punto(d);
    float b = d.punto(oc);
    float c = (oc.punto(oc)) - (this->radius * this->radius);
    float discriminant = (b * b) - ((4*a * c));
    if (discriminant > 0) {
        float temp = (0.5*(-b - sqrt(discriminant))/a);
        float temp2 = (0.5*(-b + sqrt(discriminant))/a);
        emite = this->emision;
        material = this->material;
        if (temp > temp2) {
            distancia = temp2;

            Vectores dondeGolpea = o.sumarVector(d.multiplicarValor(distancia));
            normalGolpe = dondeGolpea.restarVector(oc);     //Vector resultante de origen - golpe
            normalGolpe.normalizar();

            return true;
        }
        distancia = temp;

        Vectores dondeGolpea = o.sumarVector(d.multiplicarValor(distancia));
        normalGolpe = dondeGolpea.restarVector(oc);     //Vector resultante de origen - golpe
        normalGolpe.normalizar();
        return true;
    }
    return false;
*/
    
    /*
    Vectores d = r2.direccion;
    Vectores o = r2.origen;
    Vectores c = this->center;
    float r = radius;

    float t1, t2;

    Vectores l = c.restarVector(o);
    float tca = d.punto(l);

    if(tca < 0) return false;

    float d2 = l.punto(l) - tca * tca;

    if (d2 > r * r) return false; 

    float thc = sqrt((r*r)-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if(t1 < 0){
            return false;
        }
    }

    emite = this->emision;
    distancia = t1;
    material = this->material;
    Vectores dondeGolpea = o.sumarVector(d.multiplicarValor(distancia));
    normalGolpe = dondeGolpea.restarVector(c);     //Vector resultante de origen - golpe
    normalGolpe.normalizar();
    */
};

Emission Sphere::getColor() const{
    return emision;
}

string Sphere::queSoy() const{
    return "esfera";
}

Vectores Sphere::sacarVectorObjeto() const{
    return center;
}

float Sphere::getRefractiveIndex() const {
    return refractiveIndex;
}

Material Sphere::getMaterial() const {
    return material;
}
/*
//Esferas test
Vectores bolaAux1(1.0, 1.0, 4.0, 1);
Sphere bola2(bolaAux1,2.5,color1);
float distancia;
Ray rayTest(sensorCentro, sensorApuntaF);
Emission colorAux;
bool tst = bola2.ray_intersect(rayTest, colorAux, distancia);
cout << "Resultado: "<<tst<<", Distancia: "<<distancia<<", color: "<<colorAux.red<<colorAux.green<<colorAux.blue<<endl;
*/