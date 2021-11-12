#pragma once

#include "pixel.hpp"

Pixel::Pixel(){
}

Pixel::Pixel(float Rgb, float rGb, float rgB){
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}

void Pixel::update(Pixel pixelNuevo){
    this->R = pixelNuevo.R;
    this->G = pixelNuevo.G;
    this->B = pixelNuevo.B;
}

void Pixel::update(colour pixelNuevo){
    this->R = pixelNuevo.R;
    this->G = pixelNuevo.G;
    this->B = pixelNuevo.B;
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

Pixel media(vector<Pixel> conjunto){
    float redValue=0.0;
    float greenValue=0.0;
    float blueValue=0.0;
    int pixeles=0;
    for (Pixel pixel : conjunto){
        redValue = redValue + pixel.R;
        greenValue = greenValue + pixel.G;
        blueValue = blueValue + pixel.B;
        pixeles++;
    }
    if(pixeles == 0){
        pixeles=1;
    }
    return Pixel(redValue/pixeles , greenValue/pixeles , blueValue/pixeles);
}

/*
Pixel Pixel::operator*(const Pixel& b){
    return Pixel(this->R*b.R, this->G*b.G, this->B*b.B);
}*/
Pixel Pixel::operator+(const Pixel& b){
    return Pixel((this->R+b.R), (this->G+b.G), (this->B+b.B));
}
Pixel Pixel::operator*(const Pixel& b){
    return Pixel((this->R*b.R), (this->G*b.G), (this->B*b.B));
}
Pixel Pixel::operator*(const float& b){
    return Pixel(this->R*b, this->G*b, this->B*b);
}
Pixel Pixel::operator/(const float& b){
    return Pixel(this->R/b, this->G/b, this->B/b);
}

ostream& operator<<(ostream& os, const Pixel& vec)
{
    os << "R: "<< vec.R << "| G: " << vec.G << "| B: " << vec.B;
    return os;
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