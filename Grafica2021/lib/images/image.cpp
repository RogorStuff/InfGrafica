#pragma once

#include "image.hpp"

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
            //m = 1;

            getline(fileReader,name);

            fileReader >> width >> height >> c; 

            imageMatrix.resize(width*height);

            int r,g,b;
            total = height*width;
            for (int i = 0; i < total; i++){
                fileReader >> r >> g >> b;
                Pixel pixel(r,g,b);
                pixel.R = pixel.R * m / 65535;  //65535
                pixel.G = pixel.G * m / 65535;
                pixel.B = pixel.B * m / 65535;
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

void Image::saveLDR(string newFileName){
    ofstream fileTarget(newFileName+".ppm");
    if (fileTarget.is_open()){
        cout << "Inicia guardado"<<endl;
        fileTarget << this->formatID << endl;
        fileTarget << "#MAX=" <<this->m << endl;
        fileTarget << "# " <<newFileName<<".ppm"<< endl;
        fileTarget << this->width<<" " <<this->height<< endl;
        fileTarget << 255 << endl;

        int pos=0;
        for (int i=0; i<this->height;i++){    //this->height
            for (int j=0; j<this->width;j++){ //this->width
                fileTarget << round(this->imageMatrix[pos].R*255/m) << " "<< round(this->imageMatrix[pos].G*255/m) << " "<< round(this->imageMatrix[pos].B*255/m) << "     ";
                pos++;
            }
            if ( i % 20 == 0){
                cout<<i<<"/"<<this->height<<endl;
            }
            fileTarget << endl;
        }
        fileTarget.close();
        cout << "Acaba guardado"<<endl;

    }else{
        cout << "No se pudo abrir o encontrar la imagen" << endl;
    }
}


float Image::getBiggerValueRGB(){

    int pos=0;
    float max = 0;
    for (int i=0; i<this->height;i++){    //this->height
        for (int j=0; j<this->width;j++){ //this->width
            if (this->imageMatrix[pos].R > max) {max = this->imageMatrix[pos].R;}
            if (this->imageMatrix[pos].G > max) {max = this->imageMatrix[pos].G;}
            if (this->imageMatrix[pos].B > max) {max = this->imageMatrix[pos].B;}
            
            pos++;
        }
    }
    return max;

}

void Image::save(string newFileName){
    ofstream fileTarget(newFileName + ".ppm");
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
                fileTarget << (int)(this->imageMatrix[pos].R*(float)this->c) << " "<< (int)(this->imageMatrix[pos].G*(float)this->c) << " "<< (int)(this->imageMatrix[pos].B*(float)this->c) << "     ";
                pos++;
            }
            if (i % 10000 == 0){
                cout<< "\r" << "Guardado " << (float)i*width*100/total << " %" ;
            }
            //cout<<i<<"/"<<this->height<<endl;
            fileTarget << endl;
        }
        fileTarget.close();
        cout << "\r" << "Guardado " << "100" << " %";
        cout << endl <<"Acaba guardado"<<endl;

    }else{
        cout << "No se pudo abrir o encontrar la imagen" << endl;
    }
}