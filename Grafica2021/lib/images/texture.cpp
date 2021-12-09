#pragma once

#include "texture.hpp"

Texture::Texture(){
}

Texture::Texture(string fileName){
    ifstream fileReader(fileName);
    if (fileReader.is_open()){

        float rValue;
        string line;

        //Leemos las 2 primeras líneas
        getline(fileReader, line);
        getline(fileReader, line);

        //Leemos el ancho y alto
        fileReader >> this->width;
        fileReader >> this->height;
        this->max = this->width*this->height;

        //Otras 2 lineas a la basura
        getline(fileReader, line);
        getline(fileReader, line);

        //Empezamos a leer los pixeles
        while(true){
                fileReader >> rValue;
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura
                if (rValue < 0){break;}
                float gValue, bValue;
                fileReader >> gValue;
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura
                fileReader >> bValue;
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura
                Pixel nuevo = Pixel(rValue/255, gValue/255, bValue/255);
                this->contenido.push_back(nuevo);

            rValue = -1;
        }

        cout << "Textura Cargada" << endl;
    }else{
        cout << "No se pudo cargar la textura" << endl;
    }
}

Pixel Texture::getPixel(int x_, int y_){
    int ancho = this->width;
    int alto = this->height;
    return this->contenido.at((x_*ancho + y_)%(ancho*alto));
}
