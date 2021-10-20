#include "lib/shapes/plane.hpp"
#include "lib/shapes/sphere.hpp"
#include "lib/shapes/sceneReader.cpp"

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

    //cout<<planos.size()<<endl;
    //planos[0].color.printColour();
    //cout<<endl;
    //planos[1].printCenter();
    cout<<planos[1].center<<endl;
    cout<<planos[1].color<<endl;
    /*
    cout<<planos[0]->printNormal()<<endl;
    cout<<planos[0]->color.R<<endl;
    cout<<planos[0]->color.G<<endl;
    cout<<planos[0]->color.B<<endl;*/
    //cout<<planos[0]->color.printColour()<<endl;

}