#include "vec3.cpp"
#include "matrix.cpp"
#include "iostream"
#include "planet.cpp"

using namespace std;
# define M_PI           3.14159265358979323846

int main(){

    vec3 centro (5, 5, 5, 0);
    vec3 normal (0, 2, 0, 0);
    vec3 ciudad (5, 5, 4, 0);

    planet Espanita (centro, normal, ciudad, 0, M_PI/2);

    vec3 primerEjeCoordenadasMundo (0.0, (normal.modulo()/2), 0.0, 0);                                  //Eje Y
    vec3 segundoEjeCoordenadasMundo =  rotarX( M_PI/2, primerEjeCoordenadasMundo);                      //Eje X
    vec3 tercerEjeCoordenadasMundo = cross(primerEjeCoordenadasMundo, segundoEjeCoordenadasMundo);      //Eje Z

    cout << "primerEjeCoordenadasMundo esta en: " <<primerEjeCoordenadasMundo.x << " " << primerEjeCoordenadasMundo.y << " " << primerEjeCoordenadasMundo.z << endl;
    vec3 aux = rotarX( Espanita.inclination, primerEjeCoordenadasMundo);

    cout << "aux esta en: " <<aux.x << " " << aux.y << " " << aux.z << " al haber usado inclination = " << Espanita.inclination << endl;
    vec3 vectorCentro_PS = rotarY( Espanita.azimuth, aux);

    cout << "vectorCentro_PS esta en: " <<vectorCentro_PS.x << " " << vectorCentro_PS.y << " " << vectorCentro_PS.z << " al haber usado azimuth = " << Espanita.azimuth << endl;
    vec3 posicionPSOnWorld = vectorCentro_PS + centro;

    cout << "La PS esta en: " <<posicionPSOnWorld.x << " " << posicionPSOnWorld.y << " " << posicionPSOnWorld.z << endl;

    float a = Espanita.inclination; float i = Espanita.azimuth;
    vec3 vectorParametrico (sin(i) * sin(a), sin(i) * cos(a), cos(i), 0);
    vec3 confirmacionParametrica = centro + vectorParametrico*(normal.modulo()/2);

    cout << "Por parametrico: " <<confirmacionParametrica.x << " " << confirmacionParametrica.y << " " << confirmacionParametrica.z << endl;


    


    return 0;
}