#pragma once

#include "pixel.hpp"

Pixel::Pixel(){
}

Pixel::Pixel(int Rgb, int rGb, int rgB){
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