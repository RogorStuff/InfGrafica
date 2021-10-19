#pragma once

#include "plane.cpp"
#include "sphere.cpp"
#include "colour.cpp"
#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

/*
*   El formato de las imágenes será tal que:
*   tipo(sphere/plane)
*   center.X center.Y center.Z
*   normal.X normal.Y normal.Z/radius (dependiendo del tipo)
*   color.R color.G color.B (aún no incluido)
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

            if (type == "sphere"){

                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> radius; 
                fileReader >> color[0] >> color[1] >> color[2]; 
                vec3 newCenter(center[0], center[1], center[2], 0);
                sphere newSphere(newCenter, radius, colour(color[0], color[1], color[2]));
                esferas.push_back(newSphere);

            }else if (type == "plane"){

                fileReader >> center[0] >> center[1] >> center[2]; 
                fileReader >> normal[0] >> normal[1] >> normal[2]; 
                fileReader >> color[0] >> color[1] >> color[2]; 
                cout<<color[0] << " - " << color[1]<< " - " <<color[2]<<endl;
                vec3 newCenter(center[0], center[1], center[2], 0);
                vec3 newNormal(normal[0], normal[1], normal[2], 0);
                colour newColor(color[0], color[1], color[2]);
                cout<<newColor.R << " - " << newColor.G<< " - " <<newColor.B<<endl;
                //cout<<newColor.printColour()<<endl;
                plane newPlane(newCenter, newNormal, newColor);
                planos.push_back(newPlane);

            }else{
                cout<<"Paso algo raro"<<endl;
                cout<<type<<endl;
            }
            type = "";

        }

        cout << "Escenario guardado" << endl;
    cout<<planos.size()<<endl;
    planos[0].printCenter();
        return true;
    }else{
        cout << "No se pudo abrir o encontrar el escenario" << endl;
        return false;
    }
}