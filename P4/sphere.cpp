#include "sphere.hpp"

Sphere::Sphere(){
}

Sphere::Sphere(Vectores Ncentro, float Nradio, Emission Nemision){
    center=Ncentro;
    radius=Nradio;
    emision=Nemision;
}

bool Sphere::ray_intersect(Ray& r, Emission& emite, float& distancia) const{
    Vectores d = r.direccion;
    Vectores o = r.origen;

    Vectores oc = this->center;

    float t_min = -1;
    float t_max = 999999999999999;

    float a = d.punto(d);
    float b = oc.punto(d);
    float c = (oc.punto(oc)) - (this->radius * this->radius);
    float discriminant = (b * b) - ((a * c));
    if (discriminant > 0) {
        float temp = fabs((-b - sqrt(discriminant)) / a);
        float temp2 = fabs((-b + sqrt(discriminant)) / a);
        emite = this->emision;
        if (temp > temp2) {
            distancia = temp2;
            return true;
        }
        distancia = temp;
        return true;
    } 
    return false;
};


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