#pragma once

#include "plane.cpp"
#include "sphere.cpp"
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

        while(getline(fileReader, type, ' ')){

            //getline(fileReader,type,' ');   //Leemos el tipo de obstáculo

            /*type.erase(std::find_if(type.rbegin(), type.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), type.end());*/


            if (type == "sphere"){

                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> radius; 
                fileReader >> color[0] >> color[1] >> color[2]; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                colour newColor(color[0], color[1], color[2]);
                sphere newSphere(newCenter, radius, newColor);
                esferas.push_back(newSphere);
                getline(fileReader, line);  //Leemos el salto de línea y lo guardamos en la basura

            }else if (type == "plane"){

                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> normal[0] >> normal[1] >> normal[2]; 
                fileReader >> color[0] >> color[1] >> color[2]; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                vec3 newNormal(normal[0], normal[1], normal[2], 0);
                colour newColor(color[0], color[1], color[2]);
                //cout<<newColor.printColour()<<endl;
                plane newPlane(newCenter, newNormal, newColor);
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