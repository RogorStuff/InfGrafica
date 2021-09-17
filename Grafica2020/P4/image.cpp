#pragma once

#include "image.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

image::image(){}

image::image(string fileName, bool nueva, int Nwidth, int Nheight){ //P3 #MAX=48 # forest_path.ppm 2048 1536 10000000
    if(!nueva){
        ifstream fileReader(fileName);
        if (fileReader.is_open()){

            getline(fileReader,formatID);   //Read format identification

            string max;
            getline(fileReader,max);        //#MAX=1656 pasar a float 1656

            string aux = max.substr(5);
            m=stof(aux);

            getline(fileReader,name);

            fileReader >> width >> height >> c; 

            imageMatrix.resize(width*height);

            int r,g,b;
            total = height*width;
            for (int i = 0; i < total; i++){
                fileReader >> r >> g >> b;
                Pixel pixel(r,g,b);
                imageMatrix[i]=pixel;
            }
            cout << "imagen guardada" << endl;
        }else{
            cout << "No se pudo abrir o encontrar la imagen" << endl;
        }
    }else{
        formatID="P3";
        m=48;
        name=fileName;
        width=Nwidth;
        height=Nheight;
        c=255;
        imageMatrix.resize(width*height);
        total = height*width;
        for (int i = 0; i < total; i++){
            Pixel pixel(0,0,0);
            imageMatrix[i]=pixel;
        }
    }
}

void image::save(string newFileName){
    string name = newFileName+".ppm";
    ofstream fileTarget(name);
    if (fileTarget.is_open()){
        cout << "Inicia guardado"<<endl;
        fileTarget << this->formatID << endl;
        fileTarget << "#MAX=" <<this->m << endl;
        fileTarget << "# " <<newFileName<<".ppm"<< endl;
        fileTarget << this->width<<" " <<this->height<< endl;
        fileTarget << this->c << endl;

        int pos=0;
        for (int i=0; i<this->height;i++){    //this->height
            for (int j=0; j<this->width;j++){ //this->width
                fileTarget << this->imageMatrix[pos].R*this->c << " "<< this->imageMatrix[pos].G*this->c << " "<< this->imageMatrix[pos].B*this->c << "     ";
                pos++;
            }
            cout<<i<<"/"<<this->height<<endl;
            fileTarget << endl;
        }
        fileTarget.close();
        cout << "Acaba guardado"<<endl;

    }else{
        cout << "No se pudo abrir o encontrar la imagen" << endl;
    }
}

image GammaCurve (image imagen, float gammaValue, int max){
    image retimage=imagen;
    cout << "Inicia gamma"<<endl;
    if (max == 0){
        for (int i = 0; i < imagen.total; i++){
            Pixel decPixel = imagen.imageMatrix[i].GammaCurve(gammaValue, imagen.c+1, imagen.m, imagen.c);
            retimage.imageMatrix[i]=decPixel;
        }
    }else{
        for (int i = 0; i < imagen.total; i++){
            Pixel decPixel = imagen.imageMatrix[i].GammaCurve(gammaValue, max, imagen.m, imagen.c);
            retimage.imageMatrix[i]=decPixel;

        }
    }
    return retimage;
}