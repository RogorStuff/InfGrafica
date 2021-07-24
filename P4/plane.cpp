#pragma once

#include "plane.hpp"


Plane::Plane(){
    material = Material();
}

Plane::Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision, Material Nmaterial, float NrefractiveIndex){
    center = Ncentro;
    emision = Nemision;
    normal = Nnormal;
    material = Nmaterial;
    refractiveIndex = NrefractiveIndex;
}

bool Plane::ray_intersect(Ray& rayo, Emission& emite, float& distancia, Material& material, Vectores &normalGolpe) const{
    //cout << "Entra en inserseccion de plano" << endl;
    float t_min = 0;
    float t_max = 99999999;

    Vectores l = rayo.direccion;
    Vectores po = this->center;
    Vectores lo = rayo.origen;
    Vectores n = normal;
    Vectores nNegado = n.negado();

    bool ret = false;

    float dist = 0.0;

    float denominator = l.punto(n);
    float denominator2 = l.punto(nNegado);


    if (denominator != 0) {
        Vectores aux = po.VectorDosPuntos(lo);
        dist =  ( aux.punto(n) ) / denominator;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            emite = this->emision;
            material.emisor = this->material.emisor;
            material = this->material;
            normalGolpe = this->normal;
            normalGolpe.normalizar();
            ret = true;
        }
    } else if (denominator2 != 0) {
        Vectores aux = po.VectorDosPuntos(lo);
        dist = ( aux.punto(nNegado) ) / denominator2;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            emite = this->emision;
            material = this->material;
            normalGolpe = this->normal;
            normalGolpe.normalizar();
            ret = true;
        }
    }

    return ret;
};

Emission Plane::getColor() const{
    return emision;
}

string Plane::queSoy() const{
    return "plano";
}

Vectores Plane::sacarVectorObjeto() const{
    return normal;
}

float Plane::getRefractiveIndex() const {
    return refractiveIndex;
}

Material Plane::getMaterial() const{
    return material;
}

//Planos test
/*
Vectores planoCentro(0.0, 0.0, 4.0, 1);
Vectores planoNormal(0.0,0.0, -1.0, 0);
Plane plano(planoCentro, planoNormal, color);

float distancia;
Ray rayTest(sensorCentro, sensorApuntaF);
bool tst = plano.ray_intersect(rayTest, color, distancia);
cout << "Resultado: "<<tst<<", Distancia: "<<distancia<<endl;

Vectores planoCentro2(0.0, 0.0, 8.0, 1);
Vectores planoNormal2(0.0, 0.0, -1.0, 0);
Plane plano2(planoCentro2, planoNormal2, color);
    
tst = plano2.ray_intersect(rayTest, color, distancia);
cout << "Resultado: "<<tst<<", Distancia: "<<distancia<<endl;
*/