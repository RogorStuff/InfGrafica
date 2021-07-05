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

bool Plane::ray_intersect(Ray& rayo, Emission& emite, float& distancia, Material& material, float &refractive) const{
    //cout << "Entra en inserseccion de plano" << endl;
    float t_min = 0;
    float t_max = 99999999;

    Vectores l = rayo.direccion;
    Vectores po = this->center;
    Vectores lo = rayo.origen;
    Vectores n = normal;

    bool ret = false;

    float dist = 0;

    float denominator = l.punto(n);
    float denominator2 = l.punto(n.negado());

    //cout << "Denomiadores creados: " << denominator << " y " << denominator2 << endl;

    if (denominator != 0) {
       //cout << "Reconocido denominador1 con valor" << endl;
        Vectores aux = (po.VectorDosPuntos(lo));
        dist =  (aux.punto(n)) / denominator;
        //cout << "dist calculada" << endl;
        if (dist < t_max && dist > t_min) {
           // cout << "Entra en el if" << endl;
            distancia = dist;
            //cout << "Dist asignada" << endl;
            emite = this->emision;
           // cout << "emite asignada" << endl;
            //cout << this->material.emisor << endl;
            //cout << material.emisor << endl;
            material.emisor = this->material.emisor;
           // cout << "Esto rula ?" << endl;
            material.reflectance = this->material.reflectance;
            //cout << "Esto rula ?" << endl;
            material = this->material;
            //cout << "material asignada" << endl;
            ret = true;
           // cout << "Valores asignados" << endl;
        }
    } else if (denominator2 != 0) {
        Vectores aux = (po.VectorDosPuntos(lo));
        dist = ( aux.punto(n.negado()) ) / denominator2;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            emite = this->emision;
            material = this->material;
            ret = true;
        }
    }
    else {ret = false;}
    //cout << "Sale de inserseccion de plano" << endl;

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