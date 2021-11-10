#pragma once

#include "vec3.cpp"

class matrix {
    public:
        vec3 U,V,W,O;  //Cada vector representa una columna

        matrix();
        matrix(vec3& U_, vec3& V_, vec3& W_, vec3& O_);
};

matrix::matrix(){}

matrix::matrix(vec3& U_, vec3& V_, vec3& W_, vec3& O_){
    U=U_;
    V=V_;
    W=W_;
    O=O_;
}

matrix inverseMatrix(matrix m){
    cout<<"test";
    vec3 u_ = inverso(m.U);
    cout<<m.U<<" "<<u_<<endl;
    vec3 v_ = inverso(m.V);
    cout<<m.V<<" "<<v_<<endl;;
    vec3 w_ = inverso(m.W);
    cout<<m.W<<" "<<w_<<endl;;
    vec3 o_ = inverso(m.O);
    cout<<m.O<<" "<<o_<<endl;;
    return matrix(u_, v_, w_, o_);
}

vec3 translation(matrix& desplazamiento, vec3& objeto){
    float X2 = objeto.x*desplazamiento.U.x + objeto.y*desplazamiento.V.x + objeto.z*desplazamiento.W.x + objeto.punto*desplazamiento.O.x;
    float Y2 = objeto.x*desplazamiento.U.y + objeto.y*desplazamiento.V.y + objeto.z*desplazamiento.W.y + objeto.punto*desplazamiento.O.y;
    float Z2 = objeto.x*desplazamiento.U.z + objeto.y*desplazamiento.V.z + objeto.z*desplazamiento.W.z + objeto.punto*desplazamiento.O.z;
    float punto2 = objeto.x*desplazamiento.U.punto+objeto.y*desplazamiento.V.punto+objeto.z*desplazamiento.W.punto+objeto.punto*desplazamiento.O.punto;
    return vec3(X2, Y2, Z2, punto2);
}

vec3 baseChange(matrix& desplazamiento, vec3& objeto){
    float X2 = objeto.x*desplazamiento.U.x+objeto.y*desplazamiento.V.x+objeto.z*desplazamiento.W.x+objeto.punto*desplazamiento.O.x;
    float Y2 = objeto.x*desplazamiento.U.y+objeto.y*desplazamiento.V.y+objeto.z*desplazamiento.W.y+objeto.punto*desplazamiento.O.y;
    float Z2 = objeto.x*desplazamiento.U.z+objeto.y*desplazamiento.V.z+objeto.z*desplazamiento.W.z+objeto.punto*desplazamiento.O.z;
    float punto2 = objeto.x*desplazamiento.U.punto+objeto.y*desplazamiento.V.punto+objeto.z*desplazamiento.W.punto+objeto.punto*desplazamiento.O.punto;
    return vec3(X2, Y2, Z2, punto2);
}

vec3 rotarVector(matrix& rotacion, vec3& objeto){
    float X2 = objeto.x*rotacion.U.x+objeto.y*rotacion.V.x+objeto.z*rotacion.W.x+objeto.punto*rotacion.O.x;
    float Y2 = objeto.x*rotacion.U.y+objeto.y*rotacion.V.y+objeto.z*rotacion.W.y+objeto.punto*rotacion.O.y;
    float Z2 = objeto.x*rotacion.U.z+objeto.y*rotacion.V.z+objeto.z*rotacion.W.z+objeto.punto*rotacion.O.z;
    float punto2 = objeto.x*rotacion.U.punto+objeto.y*rotacion.V.punto+objeto.z*rotacion.W.punto+objeto.punto*rotacion.O.punto;
    return vec3(X2, Y2, Z2, punto2);
}

vec3 rotarX(float angulo, vec3& objeto){
    vec3 U_(1,0,0,0);
    vec3 V_(0,cos(angulo),sin(angulo), 0);
    vec3 W_(0,-sin(angulo),cos(angulo), 0);
    vec3 O_(0,0,0,1);

    matrix rotacion(U_, V_, W_, O_);
    return rotarVector(rotacion, objeto);
}

vec3 rotarY(float angulo, vec3& objeto){
    vec3 U_(cos(angulo),0,-sin(angulo),0);
    vec3 V_(0,1,0,0);
    vec3 W_(sin(angulo),0,cos(angulo),0);
    vec3 O_(0,0,0,1);

    matrix rotacion(U_, V_, W_, O_);
    return rotarVector(rotacion, objeto);
}

vec3 rotarZ(float angulo, vec3& objeto){
    vec3 U_(cos(angulo),sin(angulo),0,0);
    vec3 V_(-sin(angulo),cos(angulo),0,0);
    vec3 W_(0,0,1,0);
    vec3 O_(0,0,0,1);

    matrix rotacion(U_, V_, W_, O_);
    return rotarVector(rotacion, objeto);
}
