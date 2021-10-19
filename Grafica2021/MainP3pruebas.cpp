#include "lib/shapes/plane.hpp"
#include "lib/shapes/sphere.hpp"
#include "lib/shapes/sceneReader.hpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

//Compilar: g++ -std=c++11 MainP3pruebas.cpp -o a -O3

int main () {

    vector<plane> planos;
    vector<sphere> esferas;

    bool exito = sceneReader(esferas, planos, "prueba.txt");

    cout<<planos.size()<<endl;
    planos[0].printCenter();
    cout<<planos[0].normal.x<<endl;
    cout<<planos[0].normal.y<<endl;
    cout<<planos[0].normal.z<<endl;
    /*
    cout<<planos[0]->printNormal()<<endl;
    cout<<planos[0]->color.R<<endl;
    cout<<planos[0]->color.G<<endl;
    cout<<planos[0]->color.B<<endl;*/
    //cout<<planos[0]->color.printColour()<<endl;

}