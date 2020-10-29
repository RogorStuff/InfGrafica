#include "math.h"
#include "toneMaping.cpp"
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 

using namespace std;

int main () {

    string fileName = "forest_path.ppm";
    cout << "Please enter the name of the img: ";
    //cin >> fileName;

    Image thisImg(fileName);

    Image newImg = GammaCurve (thisImg, 0.5, 0);

    newImg.save("forest2");

}
