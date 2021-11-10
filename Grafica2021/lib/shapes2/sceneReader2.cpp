#pragma once

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
*   normal.X normal.Y normal.Z/radius (dependiendo del tipo)
*   color.R color.G color.B
*/

bool sceneReader(vector<sphere> &esferas, vector<plane> &planos, string fileName){
    ifstream fileReader(fileName);
    if (fileReader.is_open()){

        string type = "";
        string line = "";
        float center[3];
        float normal[3];
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
                fileReader >> normal[0] >> normal[1] >> normal[2]; 
                fileReader >> color[0] >> color[1] >> color[2]; 
                fileReader >> diffuse >> reflective >> refractive >> refractIndex >> emisor; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                vec3 newNormal(normal[0], normal[1], normal[2], 0);
                colour newColor(color[0]/255, color[1]/255, color[2]/255);
                plane newPlane(newCenter, newNormal, newColor, diffuse, reflective, refractive, refractIndex, emisor);
                planos.push_back(newPlane);
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