#include "math.h"
#include "toneMaping.cpp"
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include <time.h>  
#include "vector.hpp"

using namespace std;

/*
class Ray{
    public:
        Vectores origen;
        Vectores direccion;
        Ray(){}
        Ray(Vectores Norigen, Vectores Ndireccion):origen(Norigen),direccion(Ndireccion){}
};*//*
class Obstacle{
    public:
        virtual bool ray_intersect(Ray& rayo, Emission& emite, float& distancia) const = 0;
};
*//*
class Sphere: public Obstacle{
    public:
        float refractiveIndex; // Refractive index (Snell's law)
        float radius;
        Emission emision;
        Vectores center;
        Sphere(Vectores Ncentro, float Nradio, Emission Nemision);
        Sphere();
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia)const override;
};

    Sphere::Sphere(Vectores Ncentro, float Nradio, Emission Nemision){
        center=Ncentro;
        radius=Nradio;
        emision=Nemision;
    }

    Sphere::Sphere(){
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
        /*    if (temp < t_max && temp > t_min) {
                emite = this->emision;
                distancia = temp;
                return true;
            }
            if (temp < t_max && temp > t_min) {
                emite = this->emision;
                distancia = temp;
                return true;
            }
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
    *//*

class Plane: public Obstacle{//Todos los planos deben mirar hacia la cámara
    public:
        Emission emision;
        Vectores normal;
        Vectores center;
        Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision);
        Plane();
        bool ray_intersect(Ray& rayo, Emission& emite, float& distancia) const override;
    
};
    Plane::Plane(Vectores Ncentro, Vectores Nnormal, Emission Nemision){
        center = Ncentro;
        emision = Nemision;
        normal = Nnormal;
    }

    Plane::Plane(){
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
    };*/

/*
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

    Image ver(vector<Obstacle*> &entorno, string imagenNombre, int anchototal, int altoTotal){
        Image imagen(imagenNombre, true, anchototal, altoTotal);        
        Emission visto;
        Pixel pixel(visto);
        float aux;

        
        float imageAspectRatio = anchototal / (float)altoTotal; 
        Matrix4x4 cameraToWorld(coordenadasU.c[0], coordenadasI.c[0], apunta.c[0], coordenadasO.c[0], 
                                coordenadasU.c[1], coordenadasI.c[1], apunta.c[1], coordenadasO.c[1],
                                coordenadasU.c[2], coordenadasI.c[2], apunta.c[2], coordenadasO.c[2],
                                0.0, 0.0, 0.0, 1.0);

        for (int miraPixel=0; miraPixel < imagen.total; miraPixel++){

            
            int alto=miraPixel/imagen.height;
            int ancho=miraPixel%imagen.height;

            float x = (2 * (alto + 0.5) / (float)anchototal - 1) * imageAspectRatio; 
            float y = (1 - 2 * (ancho + 0.5) / (float)altoTotal); 

            //Vectores rayDirection(x, y, apunta.c[2], 0);
            //Ray rayoAux(this->coordenadasO,rayDirection); //Generar rayo
            //rayoAux.direccion.traspConMatriz(cameraToWorld);

            float X1 = (float)((rand() % 20)+5)/100;
            float X2 = (float)((rand() % 20)+5)/100;
            float Y1 = (float)((rand() % 20)+5)/100;
            float Y2 = (float)((rand() % 20)+5)/100;
            vector<Ray> rayos;
            Vectores rayDirection1(x-X1/(float)anchototal, y-Y1/(float)altoTotal, apunta.c[2], 0);
            Ray rayoAux1(this->coordenadasO,rayDirection1); //Generar rayo
            rayoAux1.direccion.traspConMatriz(cameraToWorld);
            rayos.push_back(rayoAux1);
            Vectores rayDirection2(x-X2/(float)anchototal, y+Y1/(float)altoTotal, apunta.c[2], 0);
            Ray rayoAux2(this->coordenadasO,rayDirection2); //Generar rayo
            rayoAux2.direccion.traspConMatriz(cameraToWorld);
            rayos.push_back(rayoAux2);
            Vectores rayDirection3(x+X1/(float)anchototal, y-Y2/(float)altoTotal, apunta.c[2], 0);
            Ray rayoAux3(this->coordenadasO,rayDirection3); //Generar rayo
            rayoAux3.direccion.traspConMatriz(cameraToWorld);
            rayos.push_back(rayoAux3);
            Vectores rayDirection4(x+X2/(float)anchototal, y+Y2/(float)altoTotal, apunta.c[2], 0);
            Ray rayoAux4(this->coordenadasO,rayDirection4); //Generar rayo
            rayoAux4.direccion.traspConMatriz(cameraToWorld);
            rayos.push_back(rayoAux4);

            vector<Pixel> recibidos;
            for (auto ray : rayos){
                float menorDistancia=1000000.0;
                bool impactado =false;
                for (auto obstacle : entorno){
                    if(obstacle->ray_intersect(ray,visto,aux)){ 
                        impactado = true;
                        if(aux<menorDistancia){
                            pixel.update(visto);
                            menorDistancia=aux;
                        }
                    }
                }
                if(impactado){
                    recibidos.push_back(pixel);
                }
            }
            if (recibidos.size()>0){
                imagen.imageMatrix[miraPixel]=media(recibidos);

            }
        }
        return imagen;
    }
};*/

//Esferas test
    /*
    Vectores bolaAux1(1.0, 1.0, 4.0, 1);
    Sphere bola2(bolaAux1,2.5,color1);
    float distancia;
    Ray rayTest(sensorCentro, sensorApuntaF);
    Emission colorAux;
    bool tst = bola2.ray_intersect(rayTest, colorAux, distancia);
    cout << "Resultado: "<<tst<<", Distancia: "<<distancia<<", color: "<<colorAux.red<<colorAux.green<<colorAux.blue<<endl;
    

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