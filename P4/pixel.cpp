#include "pixel.hpp"
#include "math.h"
#include <vector>

using namespace std;

Pixel::Pixel(){
}

Pixel::Pixel(Emission emission){
    this->R=emission.red;
    this->G=emission.green;
    this->B=emission.blue;
}
Pixel::Pixel(float Rgb, float rGb, float rgB){
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}

void Pixel::update(Emission emission){
    this->R=emission.red;
    this->G=emission.green;
    this->B=emission.blue;
}

void Pixel::update(float Rgb, float rGb, float rgB){
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}

void Pixel::divideTotal(int divisor){
    if (divisor != 0){
        this->R = this->R/divisor;
        this->G = this->G/divisor;
        this->B = this->B/divisor;
    }
}

void Pixel::multiplicaTotal(float multiplicador){
    R = this->R*multiplicador;
    G = this->G*multiplicador;
    B = this->B*multiplicador;
}

void Pixel::multiplicaTotal(Emission multiplicador){
    R = this->R*multiplicador.red;
    G = this->G*multiplicador.green;
    B = this->B*multiplicador.blue;
}

Pixel Pixel::GammaCurve(float gamma, float max, float m, float c){
    float newR,newG,newB;
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


float getPixelValue(Pixel pixel){
    return (pixel.R+pixel.G+pixel.B)/3;
}

bool Pixel::escero(){
    return (R+G+B) < 0.03;
}

Pixel media(vector<Pixel> colores){
    float redValue=0.0;
    float greenValue=0.0;
    float blueValue=0.0;
    int pixeles=0;
    for (auto pixel : colores){
        redValue = redValue + pixel.R;
        greenValue = greenValue + pixel.G;
        blueValue = blueValue + pixel.B;
        pixeles++;
    }
    return Pixel(redValue/pixeles,greenValue/pixeles,blueValue/pixeles);
}