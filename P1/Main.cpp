#include "iostream"
#include "math.h"
using namespace std;

# define M_PI           3.14159265358979323846  /* pi */


class Vectores {
    public:    
        float c [ 3 ] ; //or std::array<float,3> c;
        int tipoPunto;
        Vectores(float x , float y , float z , int tipoDePunto);
        Vectores();
        float distAbsoluta();
        float distDosPuntos(Vectores p2);
        Vectores VectorDosPuntos(Vectores p2);
};
Vectores::Vectores(float x , float y , float z , int tipoDePunto){
    c[ 0 ] =x ; c[ 1 ] =y ; c[ 2 ] =z ; tipoPunto = tipoDePunto;
}

Vectores::Vectores() {
}

float Vectores::distAbsoluta(){
    return sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2]);
}

float Vectores::distDosPuntos(Vectores p2){
    Vectores aux (this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 1);
    return aux.distAbsoluta();
}

Vectores Vectores::VectorDosPuntos(Vectores p2){
    Vectores aux (this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 1);
    return aux;
}


class Planeta {
    public:
        Vectores centro;
        Vectores eje;
        Vectores ciudadRef;
        float azimuth;
        float inclination;
        Planeta(Vectores centro2, Vectores eje2, Vectores ciudadRef2, float azi, float incl);
        bool comprobarRadio();
} ;

Planeta::Planeta (Vectores centro2, Vectores eje2, Vectores ciudadRef2, float azi, float incl){
    centro = centro2; eje = eje2; ciudadRef = ciudadRef2; azimuth = azi; inclination = incl;
};

bool Planeta::comprobarRadio(){
    float mediaAbs = this->eje.distAbsoluta() / 2;
    float distanciaPuntos = centro.distDosPuntos(ciudadRef);

    if (fabs(mediaAbs - distanciaPuntos) < pow(10, -6)) {
        return true;
    }
    return false;
}


int main () {

    Vectores centroPl(5.0 ,5.0 ,5.0 ,1);
    Vectores ejePl(2.0, 0.0, 0.0, 0);
    Vectores ciudadRefPl(4.0, 5.0, 5.0, 1);

    Planeta pl(centroPl, ejePl, ciudadRefPl, M_PI/2, M_PI/2);

    cout << pl.comprobarRadio() << endl;
    //Hasta aqui rula loko




    return 1;
}
