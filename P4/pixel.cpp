#include "pixel.hpp"
#include "vector.hpp"
#include "material.hpp"
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
/*
Pixel getColor(const Material &material, const Vectores &position) {
    float mods[3] = {mod(position - material.vertices[0]),
                     mod(position - material.vertices[1]),
                     mod(position - material.vertices[2])};

    if (mods[0] == 0.0f) return material.colors[0];
    else if (mods[1] == 0.0f) return material.colors[1];
    else if (mods[2] == 0.0f) return material.colors[2];

    switch (vertexColor.type) {
        case VertexColor::NEAREST: {
            if (mods[0] < mods[1] && mods[0] < mods[2]) return vertexColor.colors[0];
            else if (mods[1] < mods[0] && mods[1] < mods[2]) return vertexColor.colors[1];
            else return vertexColor.colors[2];
        }
        case VertexColor::DISTANCE_WEIGHTING: {
            return ((vertexColor.colors[0] / mods[0] + vertexColor.colors[1] / mods[1] + vertexColor.colors[2] / mods[2])
                    / (1.0f / mods[0] + 1.0f / mods[1] + 1.0f / mods[2]));
        }
        case VertexColor::DISTANCE_WEIGHTING_SQUARE: {
            return ((vertexColor.colors[0] / (mods[0] * mods[0]) + vertexColor.colors[1] / (mods[1] * mods[1])
                     + vertexColor.colors[2] / (mods[2] * mods[2]))
                    / (1.0f / (mods[0] * mods[0]) + 1.0f / (mods[1] * mods[1]) + 1.0f / (mods[2] * mods[2])));
        }
    }
}*/