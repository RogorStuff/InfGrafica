#include "math.h"
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include "vector.cpp"

using namespace std;

struct Emission{
    int red;
    int green;
    int blue;

    Emission(int Ered, int Egreen, int Eblue){
        red=Ered;
        green=Egreen;
        blue=Eblue;
    }
    Emission(){}

    void getEmision(int& Rred, int& Rgreen, int& Rblue){
        Rred=red;
        Rgreen=green;
        Rblue=blue;
    }
};

struct Ray{
    Vectores origen;
    Vectores direccion;
    Ray(){}
    Ray(Vectores Norigen, Vectores Ndireccion):origen(Norigen),direccion(Ndireccion){}
};

struct Sensor{
    Vectores coordenadas;
    Vectores apunta;
    Sensor(Vectores Coordenadas, Vectores NdistanciaPlano):coordenadas(Coordenadas),apunta(NdistanciaPlano){}
};

struct Entorno{
    vector<Obstacle> objetos;
    Entorno(vector<Obstacle> Nobjetos){
        objetos.resize(Nobjetos.size());
        for (int i = 0; i < Nobjetos.size(); i++){
            //objetos[i]=Nobjetos[i];
            Obstacle menor = Nobjetos[i];
            for (int j=i+1;j<Nobjetos.size(); j++){ //ordenamos por Y, no tengo tiempo ni ganas de hacer un algoritmo de ordenar decente
                if (Nobjetos[j].center.c[1]<Nobjetos[i].center.c[1]){
                    menor=Nobjetos[j];
                }
            objetos[i]=menor;
            }
        }
    }
};

struct Obstacle{
    Vectores center;
    Obstacle(){}
    Obstacle(Vectores centro):center(centro){}
};

struct Sphere:Obstacle{
    float radius;
    Emission emision;

    Sphere(Vectores Ncentro, const float Nradio, Emission Nemision){
        center=Ncentro;
        radius=Nradio;
        emision=Nemision;
    }

    bool ray_intersect(Ray rayo, float& puntoA, float& puntoB){
        Vectores l = this->center.VectorDosPuntos(rayo.origen);
        float tca = l.punto(rayo.direccion);
        if (tca < 0) return false;
        float d2 = l.punto(l)-tca*tca;
        if(d2 > (radius*radius)) return false;
        float thc = sqrt((radius*radius) - d2); // Closest approach to surface of sphere
        puntoA = tca - thc;
        puntoB = tca + thc;
        return true;
    }
};

struct Plane:Obstacle{
    Emission emision;
    Vectores normal;

    Plane(Vectores Ncentro, Emission Nemision, Vectores Nnormal){
        center = Ncentro;
        emision = Nemision;
        normal = Nnormal;
    }

    bool ray_intersect(Vectores Vcamara, Vectores& puntoChoque){
        return true;
    }
};


int main () {



}
