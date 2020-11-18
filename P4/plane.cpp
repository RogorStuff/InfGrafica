#include "plane.hpp"

Plane::Plane(){
}

Plane::Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision){
    center = Ncentro;
    emision = Nemision;
    normal = Nnormal;
}

bool Plane::ray_intersect(Ray& rayo, Emission& emite, float& distancia) const{
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
    if (denominator != 0) {
        Vectores aux = (po.VectorDosPuntos(lo));
        dist =  (aux.punto(n)) / denominator;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            emite = this->emision;
            ret = true;
        }
    } else if (denominator2 != 0) {
        Vectores aux = (po.VectorDosPuntos(lo));
        dist = ( aux.punto(n.negado()) ) / denominator2;
        if (dist < t_max && dist > t_min) {
            distancia = dist;
            emite = this->emision;
            ret = true;
        }
    }
    else ret = false;
    return ret;
};

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