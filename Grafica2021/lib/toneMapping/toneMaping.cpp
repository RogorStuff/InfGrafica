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


Image Clamping(Image imagen, float maxClamping){  
    Image retImage = imagen;
    for (int i = 0; i < retImage.total; i++){
        if( retImage.imageMatrix[i].R > maxClamping) {retImage.imageMatrix[i].R = maxClamping;}
        if( retImage.imageMatrix[i].G > maxClamping) {retImage.imageMatrix[i].G = maxClamping;}
        if( retImage.imageMatrix[i].B > maxClamping) {retImage.imageMatrix[i].B = maxClamping;}
    }
    for (int i = 0; i < retImage.total; i++){
        retImage.imageMatrix[i].R = retImage.imageMatrix[i].R * imagen.m / maxClamping;
        retImage.imageMatrix[i].G = retImage.imageMatrix[i].G * imagen.m / maxClamping;
        retImage.imageMatrix[i].B = retImage.imageMatrix[i].B * imagen.m / maxClamping;
    }
    //retImage.c = maxClamping;
    return retImage;
}

Image Equalization(Image imagen, float maxc){ 
    Image retImage = imagen;
    for (int i = 0; i < retImage.total; i++){
        retImage.imageMatrix[i].R = retImage.imageMatrix[i].R/retImage.c * maxc;
        retImage.imageMatrix[i].G = retImage.imageMatrix[i].G/retImage.c * maxc;
        retImage.imageMatrix[i].B = retImage.imageMatrix[i].B/retImage.c * maxc;
    }
    //retImage.c = maxc;
    return retImage;
}

Image EqualizationAndClamp(Image imagen, float maxClamping){  
    Image retImage = imagen;
    for (int i = 0; i < retImage.total; i++){
        retImage.imageMatrix[i].R = retImage.imageMatrix[i].R/retImage.c * maxClamping;
        retImage.imageMatrix[i].G = retImage.imageMatrix[i].G/retImage.c * maxClamping;
        retImage.imageMatrix[i].B = retImage.imageMatrix[i].B/retImage.c * maxClamping;
    }
    //retImage.c = 255;
    return retImage;
}
//Apañao