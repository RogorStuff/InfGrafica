#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 


using namespace std;

class Pixel {
    public:
        float R;
        float G;
        float B;
        Pixel();
        Pixel(float Rgb, float rGb, float rgB);
        Pixel GammaCurve(float gamma, int max, float m, int c);
};

Pixel::Pixel(){
}

Pixel::Pixel(float Rgb, float rGb, float rgB){
    this->R=Rgb;
    this->G=rGb;
    this->B=rgB;
}

Pixel Pixel::GammaCurve(float gamma, int max, float m, int c){
    if (this->R<max){
        float Rdec = this->R*m/c;
        float valorAux = pow(Rdec,1/gamma);
        this->R = valorAux*c/m;
    }else{
        this->R=max;
    }

    if (this->G<max){
        float Gdec = this->G*m/c;
        float valorAux = pow(Gdec,1/gamma);
        this->G = valorAux*c/m;
    }else{
        this->G=max;
    }
    
    if (this->B<max){
        float Bdec = this->B*m/c;
        float valorAux = pow(Bdec,1/gamma);
        this->B = valorAux*c/m;
    }else{
        this->B=max;
    }
}

class Image {
    public:
        string formatID;
        float m;
        string name;
        int width, height;
        int c;
        vector<Pixel> imageMatrix; //imageMatrix[height][width]
        Image();
        Image(string fileName);
};

Image::Image(){
}

Image::Image(string fileName){
    ifstream fileReader(fileName);
    if (fileReader.is_open()){

        getline(fileReader,formatID);   //Read format identification

        string max;
        getline(fileReader,max);        //#MAX=1656 pasar a float 1656

        string aux = max.substr(5);
        m=stof(aux);

        getline(fileReader,name);

        fileReader >> width >> height >> c;

        cout << formatID << endl;
        cout << m << endl;
        cout << name << endl;
        cout << width << " " << height << endl;
        cout << c << endl;

        imageMatrix.resize(width*height);

        int r,g,b;
        int total = height*width;
        for (int i = 0; i < total; i++){
            fileReader >> r >> g >> b;
            Pixel pixel(r,g,b);
            imageMatrix[i]=pixel;
        }

        cout << "Imagen guardada" << endl;
    }else{
        cout << "No se pudo abrir o encontrar la imagen" << endl;
    }
}

void GammaCurve (Image imagen, float gammaValue, int max){

    int total = imagen.height*imagen.width;
    for (int i = 0; i < total; i++){
        Pixel decPixel = imagen.imageMatrix[i].GammaCurve(gammaValue, max, imagen.m, imagen.c);
        imagen.imageMatrix[i]=decPixel;
    }
    
}