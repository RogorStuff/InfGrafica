#include "math.h"
#include "toneMaping.cpp"
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
    void calibrate(float X, float Y, float Z){

    }
};

struct Obstacle{
    Vectores center;
    Obstacle(){}
    Obstacle(Vectores centro):center(centro){}
    bool ray_intersect(Ray rayo, Emission emite);
};

struct Sphere:Obstacle{
    float radius;
    Emission emision;

    Sphere(Vectores Ncentro, const float Nradio, Emission Nemision){
        center=Ncentro;
        radius=Nradio;
        emision=Nemision;
    }

    bool ray_intersect(Ray rayo, Emission& emite){
        Vectores l = this->center.VectorDosPuntos(rayo.origen);
        float tca = l.punto(rayo.direccion);
        if (tca < 0) return false;
        float d2 = l.punto(l)-tca*tca;
        if(d2 > (radius*radius)) return false;
        float thc = sqrt((radius*radius) - d2); // Closest approach to surface of sphere
        emite = this->emision;
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

    bool ray_intersect(Ray rayo, Emission emite){
        return false;
    }
};

struct Entorno{
    vector<Obstacle> objetos;
    Entorno(){}
    Entorno(vector<Obstacle> Nobjetos){
        objetos.resize(Nobjetos.size());
        objetos=Nobjetos;
    }
    void add(Obstacle item){
        int size =objetos.size();
        auto objetosAux = objetos.insert(objetos.begin()+size,item);
    }
};

struct Sensor{
    Vectores coordenadas;
    Vectores apunta;
    Sensor(Vectores Coordenadas, Vectores NdistanciaPlano):coordenadas(Coordenadas),apunta(NdistanciaPlano){}
    Image ver(Entorno entorno, string imagenNombre, int ancho, int alto){
        Image imagen("test", true, 10, 10);
        Emission visto;
        for (int miraPixel=0;miraPixel<imagen.total;miraPixel++){
            int alto=miraPixel/imagen.height;
            int ancho=miraPixel%imagen.height;
        }
        for (int i=0;i<entorno.objetos.size();i++){
             rayoAux(this->coordenadas,this->apunta);

            if(entorno.objetos[i].ray_intersect)
        }
        return imagen;
    }
};


int main () {
    Vectores bolaAux1(5.0,5.0,8.0,1);
    Emission color(500,500,500);
    Sphere bola1(bolaAux1,1.0,color);
    Entorno entorno;
    entorno.add(bola1);
    //Image imagen("test", true, 10, 10);
    //imagen.save("test");
    Vectores sensorCentro(5.0,5.0,1.0,1);
    Vectores sensorApunta(0.0,0.0,1.0,0);
    Sensor sensor(sensorCentro,sensorApunta);
    Imagen visto = sensor.ver(entorno,"test",10,10);
    visto.save("test");
}
