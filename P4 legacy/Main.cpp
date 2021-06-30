#include "emission.cpp"
#include "image.cpp"
#include "pixel.cpp"
#include "sensor.cpp"
#include "plane.cpp"
#include "sphere.cpp"
#include "material.cpp"
#include "ray.cpp"
#include "reflectance.cpp"

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h> 
#include <vector>
#include <time.h>

using namespace std;

int main () {
    srand (time(NULL));
    
    Vectores sensorCentro(0.0, 0.0, 0.0, 1);
    Vectores sensorApuntaF(0.0, 0.0, 1.0, 0);
    Vectores sensorApuntaI(1.0, 0.0, 0.0, 0);
    Vectores sensorApuntaU(0.0, 1.0, 0.0, 0);
    Sensor sensor(sensorCentro,sensorApuntaU,sensorApuntaI,sensorApuntaF);

    Material materialIluminado;
    materialIluminado.Emitter();
    Material materialReflector;
    materialReflector.Reflector(float(1.0), float(0.2), float(0.2), float(0.2));
/*
    Vectores planoCentro1(4.0, 0.0, 4.0, 1);
    Vectores planoNormal1(-1.0, 0.0, 0.0, 0);
    Emission color1(1, 0, 0);
    Plane plano1(planoCentro1, planoNormal1, color1, materialReflector, 0.0);
    
    Vectores planoCentro2(-4.0, 0.0, 4.0, 1);
    Vectores planoNormal2(1.0, 0.0, 0.0, 0);
    Emission color2(0, 1, 0);
    Plane plano2(planoCentro2, planoNormal2, color2, materialReflector, 0.0);
*/
    Emission visto;
        float distancia;
        Pixel pixelaux;
        Obstacle* obstaculoGolpeado;
        float menorDistancia=1000000.0;
        Material materialGolpeado;
        Material materialFinal;
        float refractive;


    Vectores planoCentro3(0.0, 0.0, 8.0, 1);
    Vectores planoNormal3(0.0, 1.0, -1.0, 0);
    Emission color3(1, 1, 1);
    Plane plano3(planoCentro3, planoNormal3, color3, materialReflector, 0.0);

    Vectores origenpl(0, 0, 0, 1);
    Vectores direccionpl(0, 0, 1, 0);
    Ray raypl(origenpl, direccionpl);
    bool empty2 = plano3.ray_intersect(raypl,visto,distancia, materialGolpeado, refractive);
    if (!empty2){
        cout << "victor eres autista" << endl;
    }
    Vectores nuevoOrigen2;
    nuevoOrigen2 = nuevoOrigen2.calculaPunto(raypl.origen, raypl.direccion, menorDistancia);
    Vectores nuevaDir2 = nuevaDireccion(SPECULAR, nuevoOrigen2, raypl.direccion, plano3.queSoy() , plano3.sacarVectorObjeto(), 0.0); 
    cout << "RESULTADO QUE TIENE QUE SER HACIA ESPAÑITA " << nuevaDir2.c[0] << " " << nuevaDir2.c[1] << " " << nuevaDir2.c[2] << " " <<endl;

/*
    
    Vectores planoCentro4(0.0, -4.0, 4.0, 1);
    Vectores planoNormal4(0.0, 1.0, 0.0, 0);
    Emission color4(0, 0, 1);
    Plane plano4(planoCentro4, planoNormal4, color4, materialReflector, 0.0);
*/
    //Techo
    Vectores planoCentro5(0.0, 4.0, 4.0, 1);
    Vectores planoNormal5(0.0, -1.0, 0.0, 0);
    Emission color5(0, 0, 1);
    Plane plano5(planoCentro5, planoNormal5, color5, materialIluminado, 0.0);
    
    Vectores bolaAux1(0.0, 0.0, 5.0, 1);
    float radio = 2;
    Emission colorSphere(0.5, 0, 0.5);
    Sphere bola1(bolaAux1,radio,colorSphere, materialReflector, 0.0);
/*
    Vectores origen(0, 0, 0, 1);
    Vectores direccion(0.25, 0.25, 1, 0);
    Ray ray(origen, direccion);
    
    bool empty = bola1.ray_intersect(ray,visto,distancia, materialGolpeado, refractive);
    if (!empty){
        cout << "victor eres autista" << endl;
    }

    Vectores nuevoOrigen;
    nuevoOrigen = nuevoOrigen.calculaPunto(ray.origen, ray.direccion, menorDistancia);
    Vectores nuevaDir = nuevaDireccion(SPECULAR, nuevoOrigen, ray.direccion, "esfera" , bola1.sacarVectorObjeto(), 0.0);
    cout << nuevaDir.c[0] << " " << nuevaDir.c[1] << " " << nuevaDir.c[2] << " " <<endl;


/*
    vector<Obstacle*> scene;
    scene.push_back(&plano1);
    scene.push_back(&plano2);
    scene.push_back(&plano3);
    scene.push_back(&plano4);
    scene.push_back(&plano5);
    scene.push_back(&bola1);

    Obstacle* aux = scene.at(0);
    cout << aux->sacarVectorObjeto().c[0] <<" "<< aux->sacarVectorObjeto().c[1] <<" "<< aux->sacarVectorObjeto().c[2] <<" " << endl;
    Image imagen("patata", true, 100, 100);
    imagen = sensor.ver(scene, "patata", 100, 100);

    imagen.save("patata");*/
    
}
