#include "math.h"
#include "toneMaping.cpp"
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include "vector.cpp"

using namespace std;


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
    bool ray_intersect(Ray rayo, Emission& emite, float& distancia);
};

struct Sphere:Obstacle{
    float radius;
    Emission emision;

    Sphere(Vectores Ncentro, const float Nradio, Emission Nemision){
        center=Ncentro;
        radius=Nradio;
        emision=Nemision;
    }

    bool ray_intersect(Ray rayo, Emission& emite, float& distancia){
        
        Vectores d = this->center.VectorDosPuntos(rayo.origen);
        float choca = d.punto(rayo.direccion);
        if (choca < 0.0) return false;
        float d2 = d.punto(d)-choca*choca;
        if(d2 >(radius*radius)) return false;
        float valorMasMenos = sqrtf(this->radius*this->radius - d2);
        float valorMenos = choca - valorMasMenos;
        float valorMas = choca + valorMasMenos;
        if (valorMenos < 0) valorMenos = valorMas;
        if (valorMenos < 0) return false;
        distancia=valorMenos;
        emite = this->emision;
        return true;
    }
};

struct Plane:Obstacle{
    Emission emision;
    Vectores normal;

    Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision){
        center = Ncentro;
        emision = Nemision;
        normal = Nnormal;
    }

    bool ray_intersect(Ray rayo, Emission& emite, float& distancia){

        if(rayo.direccion.punto(this->normal)==0){
            cout<<"Perpendicular"<<endl;
            return false;
        }
        float on = rayo.origen.punto(this->normal);
        float con = (this->center.distAbsoluta()+on);
        float dn = rayo.direccion.punto(this->normal);
        float t = -(con/dn);
        if(t>0.0){
            distancia = fabs((this->center.distAbsoluta()+on)/dn);
            emite=this->emision;
            return true;
        }
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
    Vectores coordenadasO;
    Vectores coordenadasU;
    Vectores coordenadasI;
    Vectores apunta;
    Sensor(Vectores CoordenadasO, Vectores CoordenadasU, Vectores CoordenadasI, Vectores NdistanciaPlano):coordenadasO(CoordenadasO),coordenadasU(CoordenadasU),coordenadasI(CoordenadasI),apunta(NdistanciaPlano){}
    void rotarSensor(float anguloX, float anguloY, float anguloZ){
        coordenadasU.rotarX(anguloX);
        coordenadasU.rotarY(anguloY);
        coordenadasU.rotarZ(anguloZ);
        coordenadasI.rotarX(anguloX);
        coordenadasI.rotarY(anguloY);
        coordenadasI.rotarZ(anguloZ);
        apunta.rotarX(anguloX);
        apunta.rotarY(anguloY);
        apunta.rotarZ(anguloZ);
    }
    Image ver(Entorno entorno, string imagenNombre, int ancho, int alto){
        Image imagen("test", true, 10, 10);
        Matrix4x4 cambioBaseTrayectoria (   apunta.c[0], 0.0, 0.0, coordenadasO.c[0],
                                            0.0, apunta.c[1], 0.0, coordenadasO.c[1],
                                            0.0, 0.0, apunta.c[2], coordenadasO.c[2],
                                            0.0, 0.0, 0.0, 1.0
      );
        Matrix4x4 vueltaBaseTrayectoria (   1.0, 0.0, 0.0, coordenadasO.c[0],
                                            0.0, 1.0, 0.0, coordenadasO.c[1],
                                            0.0, 0.0, 1.0, coordenadasO.c[2],
                                            0.0, 0.0, 0.0, 1.0
        );
        
        Emission visto;
        Pixel pixel(visto);
        float aux;
        for (int miraPixel=0;miraPixel<imagen.total;miraPixel++){
            bool impactado =false;
            int alto=miraPixel/imagen.height;
            int ancho=miraPixel%imagen.height;
            Ray rayoAux(this->coordenadasO,this->apunta); //Generar rayo
            for (int i=0;i<entorno.objetos.size();i++){
                if(entorno.objetos[i].ray_intersect(rayoAux,visto,aux)){ //Añadir distancia al item para poner el más cercano
                    impactado = true;
                    pixel.update(visto);
                };
            }
            if (impactado){
                imagen.imageMatrix[miraPixel]=pixel;
            }
        }
        return imagen;
    }
};


int main () {   //Todos los planos deben estar en negativo
    Vectores bolaAux1(0.0, 0.0, 8.0, 1);
    Emission color(500, 500, 500);
    Sphere bola1(bolaAux1,1.0,color);
    Entorno entorno;
    entorno.add(bola1);
    Ray rayoaux(bolaAux1, bolaAux1);
    //bool aux = entorno.objetos[0].ray_intersect(rayoaux, color);
    //Image imagen("test", true, 10, 10);
    //imagen.save("test");
    Vectores sensorCentro(0.0, 0.0, 3.0, 1);
    Vectores sensorApuntaF(0.0, 0.0, 1.0, 0);
    Vectores sensorApuntaI(1.0, 0.0, 0.0, 0);
    Vectores sensorApuntaU(0.0, 1.0, 0.0, 0);
    Sensor sensor(sensorCentro,sensorApuntaU,sensorApuntaI,sensorApuntaF);

    //Esferas test
    /*
    Sphere bola2(bolaAux1,2.5,color);
    float distancia;
    Ray rayTest(sensorCentro, sensorApuntaF);
    bool tst = bola2.ray_intersect(rayTest, color, distancia);
    cout << "Resultado: "<<tst<<", Distancia: "<<distancia<<endl;
    */

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


    //Image visto = sensor.ver(entorno,"test",10,10);
    //visto.save("test");
}
