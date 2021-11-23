#pragma once

#include "../images/pixel.cpp"
#include "../scene/pointLight.cpp"
#include "plane2.cpp"
#include "sphere2.cpp"
#include "colour.cpp"
#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <algorithm> 
#include <cctype>
#include <locale>
#include <stdio.h> 

using namespace std;

/*
*   El formato de las imágenes será tal que:
*   tipo(sphere/plane)
*   center.X center.Y center.Z
*   min.x    min.y    min.z
*   max.x    max.y    max.z
*   normal.X normal.Y normal.Z/radius (dependiendo del tipo)
*   color.R color.G color.B
*/

bool sceneReader(vector<sphere> &esferas, vector<plane> &planos, pointLight &light, string fileName){
    ifstream fileReader(fileName);
    if (fileReader.is_open()){

        string type = "";
        string line = "";
        float center[3];
        float normal[3];
        float min[3];
        float max[3];
        float radius;
        float color[3];
        float diffuse;
        float reflective;
        float refractive;
        float refractIndex;
        bool emisor;

        while(getline(fileReader, type, ' ')){

            //getline(fileReader,type,' ');   //Leemos el tipo de obstáculo

            /*type.erase(std::find_if(type.rbegin(), type.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), type.end());*/


            if (type == "sphere"){

                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> radius; 
                fileReader >> color[0] >> color[1] >> color[2];
                fileReader >> diffuse >> reflective >> refractive >> refractIndex >> emisor; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                colour newColor(color[0]/255, color[1]/255, color[2]/255);
                sphere newSphere(newCenter, radius, newColor, diffuse, reflective, refractive, refractIndex, emisor);
                esferas.push_back(newSphere);
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura

            }else if (type == "plane"){

                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> min[0] >> min[1] >> min[2]; 
                fileReader >> max[0] >> max[1] >> max[2]; 
                fileReader >> normal[0] >> normal[1] >> normal[2]; 
                fileReader >> color[0] >> color[1] >> color[2]; 
                fileReader >> diffuse >> reflective >> refractive >> refractIndex >> emisor; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                vec3 newNormal(normal[0], normal[1], normal[2], 0);
                vec3 newMin(min[0], min[1], min[2], 0);
                vec3 newMax(max[0], max[1], max[2], 0);
                colour newColor(color[0]/255, color[1]/255, color[2]/255);
                plane newPlane(newCenter, normalizar(newNormal), newColor, diffuse, reflective, refractive, refractIndex, emisor);
                newPlane.setLimits(newMin, newMax);
                planos.push_back(newPlane);
                //if (newPlane.getEmisor()){std::cout << "Guardado plano" << center << " que es emisor" << emisor << std::endl;}
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura

            }else if (type == "light"){
                float potencia;
                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> potencia; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                light =  pointLight(newCenter, potencia);
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura

            }else{
                cout<<"Paso algo raro, con tipo "<<type<<endl;
            }
            type = "";

        }

        cout << "Escenario guardado" << endl;
        return true;
    }else{
        cout << "No se pudo abrir o encontrar el escenario" << endl;
        return false;
    }
}

bool textureReader(vector<Pixel> &textura, string fileName){
    ifstream fileReader(fileName);
    if (fileReader.is_open()){

        float rValue;
        string line;

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
                textura.push_back(nuevo);

            rValue = -1;
        }

        cout << "Textura Cargada" << endl;
        return true;
    }else{
        cout << "No se pudo cargar la textura" << endl;
        return false;
    }
}