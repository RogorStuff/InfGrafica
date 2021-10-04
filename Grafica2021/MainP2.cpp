#include "math.h"
#include "lib/toneMapping/toneMaping.cpp"
#include "lib/images/pixel.hpp"
#include "lib/images/image.hpp"
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

//Compilar: g++ -std=c++11 MainP2.cpp -o a -O3

int main () {

    string fileName = "forest_path.ppm";
    cout << "Please enter the name of the img: ";
    //cin >> fileName;

    Image thisImg(fileName,false,0,0);

    Image newImg = GammaCurve(thisImg, 0.5, 0);

    newImg.save("forest2");

}
