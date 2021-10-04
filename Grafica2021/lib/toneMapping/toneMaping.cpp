#pragma once

#include "../images/image.hpp"
#include "../images/pixel.hpp"

using namespace std;

Image GammaCurve (Image imagen, float gammaValue, int max){
    Image retImage = imagen;
    cout << "Inicia gamma"<<endl;
    if (max == 0){
        for (int i = 0; i < imagen.total; i++){
            Pixel decPixel = imagen.imageMatrix[i].GammaCurve(gammaValue, imagen.c+1, imagen.m, imagen.c);
            retImage.imageMatrix[i]=decPixel;
        }
    }else{
        for (int i = 0; i < imagen.total; i++){
            Pixel decPixel = imagen.imageMatrix[i].GammaCurve(gammaValue, max, imagen.m, imagen.c);
            retImage.imageMatrix[i]=decPixel;

        }
    }
    return retImage;
}