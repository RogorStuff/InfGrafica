#pragma once

#include "pixel.hpp"

Pixel::Pixel(){
}

Pixel::Pixel(float Rgb, float rGb, float rgB){
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}


Pixel Pixel::GammaCurve(float gamma, int max, float m, int c){
    int newR,newG,newB;
    if (this->R<max){
        float Rdec = this->R*m/c;
        float valorAux = pow(Rdec,1/gamma);
        newR = valorAux*c/m;
    }else{
        newR=max;
    }

    if (this->G<max){
        float Gdec = this->G*m/c;
        float valorAux = pow(Gdec,1/gamma);
        newG = valorAux*c/m;
    }else{
        newG=max;
    }
    
    if (this->B<max){
        float Bdec = this->B*m/c;
        float valorAux = pow(Bdec,1/gamma);
        newB = valorAux*c/m;
    }else{
        newB=max;
    }
    return Pixel(newR,newG,newB);
}

/*
Pixel Pixel::GammaCurve(float gamma, int max, float m, int c){
    int newR,newG,newB;
    
    float Rdec = this->R*m/c;
    float valorAux = pow(Rdec,1/gamma);
    newR = valorAux*c/m;
    newR = newR*255/c;
    if (newR > max){
        newR=max;
    }

    float Gdec = this->G*m/c;
    valorAux = pow(Gdec,1/gamma);
    newG = valorAux*c/m;
    newG = newG*255/c;
    if (newG > max){
        newG=max;
    }
    
    float Bdec = this->B*m/c;
    valorAux = pow(Bdec,1/gamma);
    newB = valorAux*c/m;
    newB = newB*255/c;       
    if ( newB > max ){
        newB=max;
    }

    return Pixel(newR,newG,newB);
}
*/