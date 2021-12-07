#pragma once

#include "plane2.hpp"

plane::plane(){
}

plane::plane(vec3 center_,vec3 normal_, colour color_, float _diffuse, float _reflective, float _refractive, float _refractIndex, bool _emisor, vec3 min_ = vec3(0, 0, 0, 0), vec3 max_ = vec3(0, 0, 0, 0)){
    this->center=center_;
    this->normal=normal_;
    this->color=color_;
    this->diffuse=_diffuse;
    this->reflective=_reflective;
    this->refractive=_refractive;
    this->refractIndex=_refractIndex;
    this->emisor=_emisor;
    this->min = min_;
    this->max = max_;
    this->hayTextura = false;
    this->ladoX = max_.x-min_.x;
    this->ladoY = max_.y-min_.y;
    this->ladoZ = max_.z-min_.z;
}

void plane::setLimits(vec3 min_, vec3 max_) {
    this->min = min_;
    this->max = max_;
}

vec3 plane::getCenter(){
    return this->center;
}

vec3 plane::getNormal(){
    return this->normal;
}

float plane::getDiffuse(){
    return this->diffuse;
}

float plane::getReflective(){
    return this->reflective;
}

float plane::getRefractive(){
    return this->refractive;
}

bool plane::getEmisor(){
    return this->emisor;
}


bool plane::ray_intersect(ray rayo, colour& tono, float& distancia, vec3& normalParam) const{

    vec3 l = rayo.direccion;
    vec3 po = this->center;
    vec3 lo = rayo.origen;
    vec3 n = this->normal;
    vec3 nNegado = negado(n);

    bool ret = false;
    float dist = 0.0;

    float denominator = dot(l, n);
    float denominator2 = dot(l, nNegado);

   /* if (rayo.direccion.y<0.34 && rayo.origen.x == 0 ){
        cout<<rayo.origen<<endl;
        cout<<rayo.direccion<<endl;
    }
*/
    if (denominator != 0.0) {
        vec3 aux = po-lo;
        dist = dot(aux, n) / denominator;
        if (dist > 0) {
            distancia = dist;
            tono = this->color;
            normalParam = n;
            vec3 puntoChoque = desplazarPunto(lo,l,distancia);
            if((100-puntoChoque.x < 0.01) && (100-puntoChoque.y < 0.01) && (puntoChoque.x < 100) && (puntoChoque.y < 100)){
                //cout<<"Punto: "<<puntoChoque<<endl;
            }
            /*if ((puntoChoque.x> max.x && puntoChoque.x< min.x) || (puntoChoque.x< max.x && puntoChoque.x> min.x) || (max.x == min.x)) {
                if ((puntoChoque.y> max.y && puntoChoque.y< min.y) || (puntoChoque.y< max.y && puntoChoque.y> min.y) || (max.y == min.y)) {
                    if ((puntoChoque.z> max.z && puntoChoque.z< min.z) || (puntoChoque.z< max.z && puntoChoque.z> min.z) || (max.z == min.z)) {*/
            if ( (puntoChoque.x <= max.x && puntoChoque.x >= min.x) || (max.x - min.x < 0.001)) {
                if ( (puntoChoque.y <= max.y && puntoChoque.y >= min.y) || (max.y - min.y < 0.001)) {
                    if ( (puntoChoque.z <= max.z && puntoChoque.z >= min.z) || (max.z - min.z < 0.001)) {
                        ret= true;
                    }  
                }
            }
            //ret= true;
        }
    } else if (denominator2 != 0.0) {
        vec3 aux = po-lo;
        dist = dot(aux, nNegado) / denominator2;
        if (dist > 0) {
            distancia = dist;
            tono = this->color;
            normalParam = nNegado;
            vec3 puntoChoque = desplazarPunto(lo,l,distancia);
            if((100-puntoChoque.x < 0.01) && (100-puntoChoque.y < 0.01) && (puntoChoque.x < 100) && (puntoChoque.y < 100)){
                //cout<<"Punto: "<<puntoChoque<<endl;
            }
            if ( (puntoChoque.x <= max.x && puntoChoque.x >= min.x) || (max.x - min.x < 0.001)) {
                if ( (puntoChoque.y <= max.y && puntoChoque.y >= min.y) || (max.y - min.y < 0.001)) {
                    if ( (puntoChoque.z <= max.z && puntoChoque.z >= min.z) || (max.z - min.z < 0.001)) {
                        ret= true;
                    }  
                }
            }
            //ret= true;
        }
    }
    return ret;
}



bool plane::ray_intersect2(ray rayo, colour& tono, float& distancia, vec3& normalParam) const{

    return false;
}


string plane::queSoy() const{
    return "plano";
}

void plane::material(float& Kd, float& Ks, float& Kr) const {
    Kd = this->diffuse;
    Ks = this->reflective;
    Kr = this->refractive;
}

bool plane::getEmisor() const {
    return emisor;
}

float plane::getRIndex() const {
    return this->refractIndex;
}

void plane::setTextura(Texture texturaNueva){
    this->textura = texturaNueva;
    this->hayTextura = true;
}

bool plane::getTextura(int x, int y, int tipo, Pixel& pixelTextura) const {
    if(this->hayTextura){
        

        //cout <<tipo<<endl;

        int posicion;
        int total;
        if(tipo == 1){
            //Normal en X
            int z2 = (x+ladoZ/2);
            if(z2<0)z2=0;
            if(z2>ladoZ)z2=ladoZ;
            int y2 = (y+ladoY/2);
            if(y2<0)y2=0;
            if(y2>ladoY)y2=ladoY;
            //cout<<(x+ladoX/2)/2<<" "<<(y+ladoY/2)/2<<endl;
            int ancho = this->textura.width;
            int alto = this->textura.height;
            total = this->textura.max;
            posicion = floor(y2*ancho + z2);
            if (posicion >= ancho*alto){
                //cout<<endl<<y2<<" respecto "<<ladoY<<" y "<<z2<<" respecto "<<ladoZ<<endl;
               // cout<<posicion<<" de total "<<ancho*alto;
                posicion = total - 1;
            }

        }else if (tipo == 2){
            //Normal en Y
            int x2 = (x+ladoX/2);
            if(x2<0)x2=0;
            if(x2>ladoX)x2=ladoX;
            int z2 = (y+ladoZ/2);
            if(z2<0)z2=0;
            if(z2>ladoZ)z2=ladoZ;
            int ancho = this->textura.width;
            int alto = this->textura.height;
            total = this->textura.max;
            posicion = floor(x2 + z2*ancho);
            if (posicion >= ancho*alto){
                //cout<<endl<<x2<<" respecto "<<ladoX<<" y "<<z2<<" respecto "<<ladoZ<<endl;
                //cout<<posicion<<" de total "<<ancho*alto;
                posicion = total - 1;
            }

        }else if (tipo == 3){

            int x2 = (x+ladoX/2);
            if(x2<0)x2=0;
            if(x2>ladoX)x2=ladoX;
            int y2 = (y+ladoY/2);
            if(y2<0)y2=0;
            if(y2>ladoY)y2=ladoY;
            //cout<<(x+ladoX/2)/2<<" "<<(y+ladoY/2)/2<<endl;
            int ancho = this->textura.width;
            int alto = this->textura.height;
            total = this->textura.max;
            posicion = floor(x2 + y2*ancho);
            if (posicion >= ancho*alto){
                cout<<endl<<x2<<" respecto "<<ladoX<<" y "<<y2<<" respecto "<<ladoY<<endl;
                cout<<posicion<<" de total "<<ancho*alto;
                posicion = total - 1;
            }

        }else{
            return false;
        }

        pixelTextura = this->textura.contenido.at(total - posicion);
    }
    return this->hayTextura;
}