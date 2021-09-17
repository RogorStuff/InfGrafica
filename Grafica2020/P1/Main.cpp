#include "iostream"
#include "math.h"
using namespace std;

# define M_PI           3.14159265358979323846  /* pi */


struct Matrix4x4 {
    
    float m[4][4];

       Matrix4x4() {
           m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
           m[0][1] = m[0][2] = m[0][3] = m[1][0] =
                m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] =
                m[3][0] = m[3][1] = m[3][2] = 0.f;
       }
       Matrix4x4(float mat[4][4]){
           for (int i = 0; i < 4; i++)
           {
               for (int j = 0; j < 4; j++)
               {
                   m[i][j] = mat[i][j];
               }
           }
       }
       Matrix4x4(float t00, float t01, float t02, float t03,
                 float t10, float t11, float t12, float t13,
                 float t20, float t21, float t22, float t23,
                 float t30, float t31, float t32, float t33){
                     m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
                     m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
                     m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
                     m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
                 }
       bool operator==(const Matrix4x4 &m2) const {
           for (int i = 0; i < 4; ++i)
               for (int j = 0; j < 4; ++j)
                   if (m[i][j] != m2.m[i][j]) return false;
           return true;
       }
       bool operator!=(const Matrix4x4 &m2) const {
           for (int i = 0; i < 4; ++i)
               for (int j = 0; j < 4; ++j)
                   if (m[i][j] != m2.m[i][j]) return true;
           return false;
       }
       friend Matrix4x4 Transpose(const Matrix4x4 &);
       void Print(FILE *f) const {
           fprintf(f, "[ ");
           for (int i = 0; i < 4; ++i) {
               fprintf(f, "  [ ");
               for (int j = 0; j < 4; ++j)  {
                   fprintf(f, "%f", m[i][j]);
                   if (j != 3) fprintf(f, ", ");
               }
               fprintf(f, " ]\n");
           }
           fprintf(f, " ] ");
       }
       static Matrix4x4 Mul(const Matrix4x4 &m1, const Matrix4x4 &m2) {
           Matrix4x4 r;
           for (int i = 0; i < 4; ++i)
               for (int j = 0; j < 4; ++j)
                   r.m[i][j] = m1.m[i][0] * m2.m[0][j] + 
                               m1.m[i][1] * m2.m[1][j] + 
                               m1.m[i][2] * m2.m[2][j] + 
                               m1.m[i][3] * m2.m[3][j];
           return r;
       }

};



class Vectores {
    public:    
        float c [ 3 ] ; //or std::array<float,3> c;
        int tipoPunto;
        Vectores(float x , float y , float z , int tipoDePunto);
        Vectores();
        float distAbsoluta();
        float distDosPuntos(Vectores p2);
        Vectores desplazarPuntoVector(Vectores p2);
        Vectores VectorDosPuntos(Vectores p2);
        Vectores ProductoVectorial(Vectores p2);
        Vectores normalizar();
        void traspConMatriz(Matrix4x4 matriz);
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
    Vectores aux (this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 0); //Todo vector debe tener un 0 en el cuarto parámetro
    return aux.distAbsoluta();
}

Vectores Vectores::desplazarPuntoVector(Vectores p2){
    Vectores aux (this->c[0]+p2.c[0], this->c[1]+p2.c[1], this->c[2]+p2.c[2], 1); //Se mantiene como punto
    return aux;
}

Vectores Vectores::VectorDosPuntos(Vectores p2){
    Vectores aux (this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 0); //Todo vector debe tener un 0 en el cuarto parámetro
    return aux;
}

Vectores Vectores::ProductoVectorial(Vectores p2){
    Vectores aux (this->c[1]*p2.c[2] - this->c[2]*p2.c[1], this->c[0]*p2.c[2] - this->c[2]*p2.c[0], this->c[0]*p2.c[1] - this->c[1]*p2.c[0], 0); //Todo vector debe tener un 0 en el cuarto parámetro
    return aux;
}

Vectores Vectores::normalizar(){
    float modulo = this->distAbsoluta();
    this->c[0] = this->c[0]/modulo;
    this->c[1] = this->c[1]/modulo;
    this->c[2] = this->c[2]/modulo;
}

void Vectores::traspConMatriz(Matrix4x4 matriz){
    float uno = this->c[0]*matriz.m[0][0] + this->c[1]*matriz.m[0][1] + this->c[2]*matriz.m[0][2] + this->tipoPunto*matriz.m[0][3];
    float dos = this->c[0]*matriz.m[1][0] + this->c[1]*matriz.m[1][1] + this->c[2]*matriz.m[1][2] + this->tipoPunto*matriz.m[1][3];
    float tres = this->c[0]*matriz.m[2][0] + this->c[1]*matriz.m[2][1] + this->c[2]*matriz.m[2][2] + this->tipoPunto*matriz.m[2][3];
    float cuatro = this->c[0]*matriz.m[3][0] + this->c[1]*matriz.m[3][1] + this->c[2]*matriz.m[3][2] + this->tipoPunto*matriz.m[3][3];
    this->c[0] = uno; this->c[1] = dos; this->c[2] = tres; this->tipoPunto = cuatro; 
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
        Vectores medioEje();
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
Vectores Planeta::medioEje(){
    Vectores aux(this->eje.c[0]/2, this->eje.c[1]/2, this->eje.c[2]/2, 1);
}


int main () {

    Vectores centroPl(5.0 ,5.0 ,5.0 ,1);
    Vectores ejePl(2.0, 0.0, 0.0, 0);
    Vectores ciudadRefPl(5.0,4.0,5.0, 1);

    Planeta pl(centroPl, ejePl, ciudadRefPl, M_PI/4, M_PI/4);

    cout << pl.comprobarRadio() << endl;

    //Vectores azul = pl.medioEje();
    Vectores x(1.0, 0.0, 0.0, 0);
    Vectores aux = pl.centro.VectorDosPuntos(pl.ciudadRef);
    Vectores z = x.ProductoVectorial(aux);
    Vectores y = x.ProductoVectorial(z);

    z.normalizar();
    y.normalizar();
    x.normalizar();

    cout <<"Eje x --> "<< x.c[0] << " "<< x.c[1] << " "<< x.c[2] << endl;
    cout <<"Eje y --> "<< y.c[0] << " "<< y.c[1] << " "<< y.c[2] << endl;
    cout <<"Eje z --> "<< z.c[0] << " "<< z.c[1] << " "<< z.c[2] << endl;




    Matrix4x4 transpuestaZ( cos(pl.inclination), -sin(pl.inclination), 0.0, 0.0, 
                            sin(pl.inclination), cos(pl.inclination) , 0.0 , 0.0,
                            0.0, 0.0 , 1.0 , 0.0,
                            0.0, 0.0, 0.0, 1.0);

    Vectores vectorATrasponer(1.0, 0.0, 0.0, 0); //Vectores (direcciones) con 0 al finaaaaal, sino ponle otro nombre
    vectorATrasponer.traspConMatriz(transpuestaZ);

    cout <<"Eje traspuesto respecto Z --> "<< vectorATrasponer.c[0] << " "<< vectorATrasponer.c[1] << " "<< vectorATrasponer.c[2] << " "<< vectorATrasponer.tipoPunto << endl;

    Matrix4x4 transpuestaY( cos(pl.azimuth), 0.0, sin(pl.azimuth), 0.0, 
                            0.0, 1.0 , 0.0 , 0.0,
                            -sin(pl.azimuth), 0.0 , cos(pl.azimuth) , 0.0,
                            0.0, 0.0, 0.0, 1.0);

    Matrix4x4 transpuestaX( 1.0, 0.0, 0.0, 0.0, 
                            0.0, cos(pl.azimuth) , -sin(pl.azimuth) , 0.0,
                            0.0, sin(pl.azimuth) , cos(pl.azimuth) , 0.0,
                            0.0, 0.0, 0.0, 1.0);

    vectorATrasponer.traspConMatriz(transpuestaX);
    Vectores vectorEstacion = vectorATrasponer;

    cout <<"Eje traspuesto respecto X y Z (eje de centro a estacion) --> "<< vectorEstacion.c[0] << " "<< vectorEstacion.c[1] << " "<< vectorEstacion.c[2] << " "<< vectorEstacion.tipoPunto <<endl;

    Vectores estacion = vectorEstacion.desplazarPuntoVector(pl.centro);
    
    cout <<"Posicion de la estacion --> "<< estacion.c[0] << " "<< estacion.c[1] << " "<< estacion.c[2] << " "<< estacion.tipoPunto <<endl;
    cout <<"Posicion del centro planetario --> "<< pl.centro.c[0] << " "<< pl.centro.c[1] << " "<< pl.centro.c[2] << " "<< pl.centro.tipoPunto <<endl;

    Matrix4x4 cambioBase (  x.c[0], y.c[0], z.c[0], pl.centro.c[0],
                            x.c[1], y.c[1], z.c[1], pl.centro.c[1],
                            x.c[2], y.c[2], z.c[2], pl.centro.c[2],
                            0.0, 0.0, 0.0, 1.0
    );

    Vectores surfaceNormal = vectorATrasponer.VectorDosPuntos(pl.centro);
    cout <<"Normal en la superficie --> "<< surfaceNormal.c[0] << " "<< surfaceNormal.c[1] << " "<< surfaceNormal.c[2] << " "<< surfaceNormal.tipoPunto <<endl;


    vectorATrasponer.traspConMatriz(cambioBase);
    cout <<"Eje en la nueva base --> "<< vectorATrasponer.c[0] << " "<< vectorATrasponer.c[1] << " "<< vectorATrasponer.c[2] << " "<< vectorATrasponer.tipoPunto <<endl;

    Matrix4x4 cambioBaseTrayectoria (  x.c[0], y.c[0], z.c[0], estacion.c[0],
                            x.c[1], y.c[1], z.c[1], estacion.c[1],
                            x.c[2], y.c[2], z.c[2], estacion.c[2],
                            0.0, 0.0, 0.0, 1.0
    );
    
    Vectores vectorAEstacion = vectorEstacion;
    vectorEstacion.traspConMatriz(cambioBaseTrayectoria);
    cout <<"Eje en la nueva base --> "<< vectorEstacion.c[0] << " "<< vectorEstacion.c[1] << " "<< vectorEstacion.c[2] << " "<< vectorEstacion.tipoPunto <<endl;

    return 1;
}
