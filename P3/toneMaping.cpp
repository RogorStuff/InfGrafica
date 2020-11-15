#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 


using namespace std;

struct Emission{
    float red;
    float green;
    float blue;

    Emission(float Ered, float Egreen, float Eblue){
        red=Ered;
        green=Egreen;
        blue=Eblue;
    }
    Emission(){}

    void getEmision(float& Rred, float& Rgreen, float& Rblue){
        Rred=red;
        Rgreen=green;
        Rblue=blue;
    }
};

class Pixel {
    public:
        float R;
        float G;
        float B;
        Pixel();
        Pixel(float Rgb, float rGb, float rgB);
        Pixel(Emission emision);
        void update(Emission emision);
        Pixel GammaCurve(float gamma, float max, float m, float c);
};

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

class Image {
    public:
        string formatID;
        float m;
        string name;
        int width, height;
        int c;
        int total;
        vector<Pixel> imageMatrix; //imageMatrix[height][width]
        Image();
        Image(string fileName, bool nueva, int Nwidth, int Nheight);
        void save(string newFileName);
};

Image::Image(){
}

Image::Image(string fileName, bool nueva, int Nwidth, int Nheight){ //P3 #MAX=48 # forest_path.ppm 2048 1536 10000000
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
            cout << "Imagen guardada" << endl;
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

void Image::save(string newFileName){
    ofstream fileTarget(newFileName+".ppm");
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

Image GammaCurve (Image imagen, float gammaValue, int max){
    Image retImage=imagen;
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