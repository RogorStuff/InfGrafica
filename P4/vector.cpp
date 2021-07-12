#pragma once

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
       
       /*Matrix4x4(Vectores X, Vectores Y, Vectores Z, Vectores K){
                     m[0][0] = X.c[0]; m[0][1] = X.c[1]; m[0][2] = X.c[2]; m[0][3] = X.tipoPunto;
                     m[1][0] = Y.c[0]; m[1][1] = Y.c[1]; m[1][2] = Y.c[2]; m[1][3] = Y.tipoPunto;
                     m[2][0] = Z.c[0]; m[2][1] = Z.c[1]; m[2][2] = Z.c[2]; m[2][3] = Z.tipoPunto;
                     m[3][0] = K.c[0]; m[3][1] = K.c[1]; m[3][2] = K.c[2]; m[3][3] = K.tipoPunto;
       }*/

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
        void setX(float X);
        void setY(float Y);
        void setZ(float Z);
        void rotarX(float angulo);
        void rotarY(float angulo);
        void rotarZ(float angulo);
        Vectores negado() const;
        float distAbsoluta() const;
        float punto(Vectores vector);
        float distDosPuntos(Vectores p2) const;
        Vectores sumarVector(Vectores p2);
        Vectores restarVector(Vectores p2);
        Vectores multiplicarVector(Vectores p2);
        Vectores multiplicarValor(float p2);
        Vectores cruce(Vectores p2);
        Vectores desplazarPuntoVector(Vectores p2);
        Vectores VectorDosPuntos(Vectores p2) const;
        Vectores ProductoVectorial(Vectores p2);
        Vectores ProductoVectorial2(Vectores p2);
        void calculaPunto(Vectores origen, Vectores direccion, float distancia);
        void normalizar();
        void traspConMatriz(Matrix4x4 matriz);
        
};

Vectores::Vectores(float x , float y , float z , int tipoDePunto){
    c[ 0 ] =x ; c[ 1 ] =y ; c[ 2 ] =z ; tipoPunto = tipoDePunto;
}

Vectores::Vectores() {
}

void Vectores::setX(float X){
    c[0]=X;
}

void Vectores::setY(float Y){
    c[1]=Y;
}

void Vectores::setZ(float Z){
    c[2]=Z;
}

void Vectores::rotarX(float angulo){
    float radianes = angulo*M_PI/180;
    Matrix4x4 rotateX(  1.0, 0.0, 0.0, 0.0, 
                        0.0, cos(radianes) , -sin(radianes) , 0.0,
                        0.0, sin(radianes) , cos(radianes) , 0.0,
                        0.0, 0.0, 0.0, 1.0);
    traspConMatriz(rotateX);    
}
void Vectores::rotarY(float angulo){
    float radianes = angulo*M_PI/180;
    Matrix4x4 rotateY(  cos(radianes), 0.0, sin(radianes), 0.0, 
                    0.0, 1.0 , 0.0 , 0.0,
                    -sin(radianes), 0.0 , cos(radianes) , 0.0,
                    0.0, 0.0, 0.0, 1.0);
    traspConMatriz(rotateY);
}

void Vectores::rotarZ(float angulo){
    float radianes = angulo*M_PI/180;
    Matrix4x4 rotateZ( cos(radianes), -sin(radianes), 0.0, 0.0, 
                            sin(radianes), cos(radianes) , 0.0 , 0.0,
                            0.0, 0.0 , 1.0 , 0.0,
                            0.0, 0.0, 0.0, 1.0);
    traspConMatriz(rotateZ);    
}

Vectores Vectores::negado () const {
    Vectores aux;
    aux.c[0] = -this->c[0];
    aux.c[1] = -this->c[1];
    aux.c[2] = -this->c[2];
    aux.tipoPunto = this->tipoPunto;
    return aux;
}

float Vectores::distAbsoluta() const{
    return sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2]);
}

float Vectores::punto(Vectores vector){
    return (c[0]*vector.c[0] + c[1]*vector.c[1] + c[2]*vector.c[2]);
}

Vectores Vectores::cruce(Vectores p2) {
    return Vectores(c[1]*p2.c[2] - c[2]*p2.c[1],c[2]*p2.c[0] - c[0]*p2.c[2],c[0]*p2.c[1] - c[1]*p2.c[0],0);
}

Vectores Vectores::sumarVector(Vectores p2){
    return Vectores(this->c[0]+p2.c[0], this->c[1]+p2.c[1], this->c[2]+p2.c[2], 0);
}

Vectores Vectores::restarVector(Vectores p2){
    return Vectores(this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 0);
}

Vectores Vectores::multiplicarVector(Vectores p2){
    return Vectores(this->c[0]*p2.c[0], this->c[1]*p2.c[1], this->c[2]*p2.c[2], 0);
}

Vectores Vectores::multiplicarValor(float p2){
    return Vectores(this->c[0]*p2, this->c[1]*p2, this->c[2]*p2, 0);
}

float Vectores::distDosPuntos(Vectores p2) const{
    Vectores aux (this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 0); //Todo vector debe tener un 0 en el cuarto parámetro
    return aux.distAbsoluta();
}

Vectores Vectores::desplazarPuntoVector(Vectores p2){
    Vectores aux (this->c[0]+p2.c[0], this->c[1]+p2.c[1], this->c[2]+p2.c[2], 1); //Se mantiene como punto
    return aux;
}

Vectores Vectores::VectorDosPuntos(Vectores p2) const{
      //Todo vector debe tener un 0 en el cuarto parámetro
    return Vectores(this->c[0]-p2.c[0], this->c[1]-p2.c[1], this->c[2]-p2.c[2], 0);
}

Vectores Vectores::ProductoVectorial2(Vectores p2){
    Vectores aux (this->c[1]*p2.c[2] - this->c[2]*p2.c[1], this->c[0]*p2.c[2] - this->c[2]*p2.c[0], this->c[0]*p2.c[1] - this->c[1]*p2.c[0], 0); //Todo vector debe tener un 0 en el cuarto parámetro
    return aux;
}

Vectores Vectores::ProductoVectorial(Vectores p2){
    Vectores aux (this->c[1]*p2.c[2] - this->c[2]*p2.c[1], this->c[2]*p2.c[0] - this->c[0]*p2.c[2], this->c[0]*p2.c[1] - this->c[1]*p2.c[0], 0); //Todo vector debe tener un 0 en el cuarto parámetro
    return aux;
}

void Vectores::calculaPunto(Vectores origen, Vectores direccion, float distancia){
    c[0] =origen.c[0]+direccion.c[0]*distancia;
    c[1] =origen.c[1]+direccion.c[1]*distancia;
    c[2] =origen.c[2]+direccion.c[2]*distancia;
    c[3] =0;
}

void Vectores::normalizar(){
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
    this->c[0] = uno; this->c[1] = dos; this->c[2] = tres; this->tipoPunto = 0; 
}