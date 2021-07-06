#pragma once

#include "sensor.hpp"
#include "vector.cpp"
#include "ray.cpp"

#include <cmath>

Sensor::Sensor(){}

Sensor::Sensor(Vectores CoordenadasO, Vectores CoordenadasU, Vectores CoordenadasI, Vectores NdistanciaPlano){
    coordenadasO=CoordenadasO;
    coordenadasU=CoordenadasU;
    coordenadasI=CoordenadasI;
    apunta=NdistanciaPlano;
}
    
void Sensor::rotarSensor(float anguloX, float anguloY, float anguloZ){
    coordenadasU.rotarX(anguloX);
    coordenadasU.rotarY(anguloY);
    coordenadasU.rotarZ(anguloZ);
    coordenadasI.rotarX(anguloX);
    coordenadasI.rotarY(anguloY);
    coordenadasI.rotarZ(anguloZ);
    apunta.rotarX(anguloX);
    apunta.rotarY(anguloY);
    apunta.rotarZ(anguloZ);
}

enum EVENT {
    REFRACTION,
    REFLECTION,
    DIFFUSE,
    SPECULAR,
    DEAD
};

/*
EVENT getRandomEvent(const Material &material) {
    // Russian roulette

    float Kd = material.reflectance.kd;
    float Ks = material.reflectance.ks;
    float kdDiffuse = material.reflectance.kdDiffuse;
    float ksDiffuse = material.reflectance.ksDiffuse;

    // cap to max value
    const float MAX = 0.99f;
    float sum = Kd + Ks + kdDiffuse + ksDiffuse;
    if (sum > MAX) {
        Kd *= MAX / sum;
        Ks *= MAX / sum;
        kdDiffuse *= MAX / sum;
        ksDiffuse *= MAX / sum;
    }

    float randomZeroToOne = random_cero_to_uno();
    if ((randomZeroToOne -= Kd) < 0) {
        // Perfect refraction case (delta BTDF)
        return REFRACTION;
    } else if ((randomZeroToOne -= Ks) < 0) {
        // Perfect specular reflectance case (delta BRDF)
        return REFLECTION;
    } else if ((randomZeroToOne -= kdDiffuse) < 0) {
        // Diffuse case 
        return DIFFUSE;
    } else if ((randomZeroToOne -= ksDiffuse) < 0) {
        // Specular case
        return SPECULAR;
    } else {
        // Path deaths
        return DEAD;
    }
}
*/

Vectores reflect(Vectores &in, Vectores &n) { //n is the normal of the surface (mirror), in is the received vector
    Vectores aux = n.multiplicarValor(in.punto(n));
    aux.multiplicarValor(2.0);
    Vectores resultado = (in.restarVector(aux));
    resultado.normalizar();
    return resultado;
}

/*
Vectores nuevaDireccion(EVENT event, Vectores position, Vectores direction,string objeto, Vectores objetoV, float obstacleRefractiveIndex){ //TODO: NO SE UTILIZA OBJETO
    cout << "Entra en nueva direccion" << endl;
    Vectores n= objetoV;
    n.normalizar();
    cout <<"confirmamos n "<< n.c[0] << " " << n.c[1] << " " << n.c[2] << " " <<endl;
    
    switch (event) {
        case REFRACTION:
        //cout<<"mal"<<endl;
            return refract(direction, n, obstacleRefractiveIndex);
        case REFLECTION:
        //cout<<"mal"<<endl;
            return reflect(direction, n);
        case DIFFUSE: {        //Rebote aleatorio
        cout<<"diffuso"<<endl;
        cout <<"Llega con "<< direction.c[0] << " " << direction.c[1] << " " << direction.c[2] << " " <<endl;
        cout <<"Choca contra "<< objetoV.c[0] << " " << objetoV.c[1] << " " << objetoV.c[2] << " " <<endl;
        cout <<"Tenemos otro vector "<< n.c[0] << " " << n.c[1] << " " << n.c[2] << " " <<endl;
            Vectores Z;
            Vectores Y;
            Vectores X;

            if (direction.punto(n) < 0) {
                // good side
                Z = n;
            } else {
                // opposite side
                Z = n.negado();
            }
            cout <<"Z es "<< Z.c[0] << " " << Z.c[1] << " " << Z.c[2] << " " <<endl;
            Y = (Z.cruce(direction));
            Y.normalizar();
            cout <<"Y es "<< Y.c[0] << " " << Y.c[1] << " " << Y.c[2] << " " <<endl;
            X = (Y.cruce(Z));
            X.normalizar();
            cout <<"X es "<< X.c[0] << " " << X.c[1] << " " << X.c[2] << " " <<endl;

            float theta = acos(sqrt(random_cero_to_uno()));
            float phi = 2.0f * (float) M_PI * random_cero_to_uno();

            Matrix4x4 matrizTransformation(X.c[0], Y.c[0], Z.c[0], position.c[0], 
                                           X.c[1], Y.c[1], Z.c[1], position.c[1],
                                           X.c[2], Y.c[2], Z.c[2], position.c[2],
                                           0.0, 0.0, 0.0, 1.0);

            Vectores aux(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta),0);
            aux.traspConMatriz(matrizTransformation);

            cout << "antes de normalizar " << aux.c[0] << " "<< aux.c[1] << " " << aux.c[2]<<endl; 
            aux.normalizar();
            cout << "despues de normalizar " << aux.c[0] << " "<< aux.c[1] << " " << aux.c[2]<<endl; 
            return aux;
        }
        case SPECULAR: {        //Rebote perfecto
            Vectores ref = reflect(direction, n);

            Vectores Z;
            Vectores Y;
            Vectores X;

            if (direction.punto(n) < localNearZero) {
                Z = direction;
                Y = n;
                X = Y.cruce(Z);
            } else {
                X = direction.cruce(ref);
                X.normalizar();
                Y = ref;
                Z = Y.cruce(X);
            }
            Matrix4x4 matrizTransformation(X.c[0], Y.c[0], Z.c[0], position.c[0], 
                                           X.c[1], Y.c[1], Z.c[1], position.c[1],
                                           X.c[2], Y.c[2], Z.c[2], position.c[2],
                                           0.0, 0.0, 0.0, 1.0);
             
            float theta = acos(random_cero_to_uno());
            float phi = 2.0f * (float) M_PI * random_cero_to_uno();

            Vectores aux(cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta),0);
            aux.traspConMatriz(matrizTransformation);
            aux.normalizar();
            return aux;
        }
        case DEAD:
            return Vectores(0.0,0.0,0.0,2); //El 2 al final indica el final
    }
}*/

/*
Pixel colorRayo(Ray ray, vector<Obstacle*> &entorno){

    Pixel pixelResultado(1.0, 1.0, 1.0);    //En cada rebote, pixel = pixel + NuevoColor*BRDF
    int rebotes = 0;
    bool sigueRebotando = true;
    bool impactadoLocal = false;

    while (sigueRebotando){

        Emission visto;
        float distancia;
        Pixel pixelaux;
        Obstacle* obstaculoGolpeado;
        float menorDistancia=1000000.0;
        Material materialGolpeado;
        Material materialFinal;
        float refractive;
        
        for (auto obstacle : entorno){          //Calcula con que obstaculo golpea
            //cout << "Entro en bucle de entornos" << endl;
            if(obstacle->ray_intersect(ray,visto,distancia, materialGolpeado, refractive)){ 
           // if(true){ 
                //cout << "Ha golpeado a algo" << endl;
                impactadoLocal = true;
                if(distancia<menorDistancia){
                    materialFinal = materialGolpeado;
                    obstaculoGolpeado = obstacle;
                    pixelaux.update(visto);
                    menorDistancia=distancia;
                    //cout<<materialFinal->isEmissor()<<" y obstaculo golpeado "<<obstaculoGolpeado->queSoy()<<endl;
                    sigueRebotando=false; //TODO eliminar
                }
            }
            //cout << "salgo de bucle iteracion" << endl;
        }
        
        if (!impactadoLocal){    //Si no impacta con nada, termina
            pixelResultado.update(0.0, 0.0, 0.0);
            impactadoLocal = false;
            sigueRebotando = false;
        }
        
        else {  //Ha impactado con algun objeto:     p = o + rayo * distnacia

            if (materialFinal.isEmissor()){  //Es una luz, conseguir color y devolver todo
                pixelResultado.multiplicaTotal(obstaculoGolpeado->getColor());
                sigueRebotando = false;
                impactadoLocal = true;
            }
            else {  //Era un objeto no luz, calcular color, preparar siguiente color, calcular dirección y seguir el loop
                EVENT eventoActual = SPECULAR; //getRandomEvent(materialFinal);
                pixelResultado.multiplicaTotal(obstaculoGolpeado->getColor());

                Vectores nuevoOrigen;
                nuevoOrigen = nuevoOrigen.calculaPunto(ray.origen, ray.direccion, menorDistancia);
                string nombreImpactado = obstaculoGolpeado->queSoy();
                Vectores objetoV;
                if(nombreImpactado=="esfera"){
                    objetoV=obstaculoGolpeado->sacarVectorObjeto();
                    objetoV.VectorDosPuntos(nuevoOrigen); //Sacamos la normal para ese punto de la esfera
                }else{
                    objetoV=obstaculoGolpeado->sacarVectorObjeto();
                }
                Vectores nuevaDir = nuevaDireccion(eventoActual, nuevoOrigen, ray.direccion, nombreImpactado ,objetoV, 0.0);    //TODO: poner refractiveindex
                //cout << nuevaDir.c[0] << " " << nuevaDir.c[1] << " " << nuevaDir.c[2] << " " <<endl;
                ray.origen = nuevoOrigen;
                ray.direccion = nuevaDir;

                rebotes++;  //Contador de
                if (eventoActual == DEAD){
                    impactadoLocal = true;
                    sigueRebotando = false;
                }
            }
        }
        
        if (pixelResultado.escero()){   //Si se ha quedado sin luz el rayo
            impactadoLocal = true;
            sigueRebotando = false;
            pixelResultado.update(0.0, 0.0, 0.0);
        }
        
       sigueRebotando = false;
    } 
    
    if (rebotes != 0){
        pixelResultado.divideTotal(rebotes);
    }
     
    cout << pixelResultado.R <<" " << pixelResultado.G << " " << pixelResultado.B << endl;
    pixelResultado.nuevoImpacto(impactadoLocal);
    return pixelResultado;
}
*/


Pixel Sensor::colorRayo(Ray ray, vector<Obstacle*> &entorno, vector<LuzPuntual*> &luces, bool &impactado){
    Vectores impacto;

    Emission visto;
    Pixel pixelaux;
    float distancia;
    float menorDistancia = INFINITY;
    for (auto obstacle : entorno){
        Material materialAux;
        float flotador = 1.0f;
        if(obstacle->ray_intersect(ray, visto, distancia, materialAux, flotador)){ 
            impactado = true;
            if(distancia<menorDistancia){
                pixelaux.update(visto);
                menorDistancia=distancia;
            }
        }
    }
    //Tenemos la distancia y el vector de golpe.
    if (impactado){
        //Si lo ve una luz puntual, dejar color. Sino negro como nuestro futuro
        Vectores nuevoOrigen;
        nuevoOrigen.calculaPunto(ray.origen, ray.direccion, menorDistancia);

        //Tenemos el punto donde impacta y el vector de luces. Para cada una, mirar si tiene luz

        bool recibeLuz;
        for (auto luz : luces){
            
            recibeLuz = true;

            //Sacamos la línea (rayo) entre el impacto y la luz "luz"
            Vectores vectorEntreImpactoYLuz=luz->coordenada;
            vectorEntreImpactoYLuz.VectorDosPuntos(nuevoOrigen);
            vectorEntreImpactoYLuz.normalizar();

            //Cogemos la distancia entre ambos puntos, para compararla con la distancia a obstáculos
            float distanciaHastaLuz = luz->coordenada.distDosPuntos(nuevoOrigen);
            
            Ray rayoActual(nuevoOrigen,vectorEntreImpactoYLuz);
            for (auto obstacle : entorno){
                Material materialAux;
                float flotador = 1.0f;
                float dist2;
                if(obstacle->ray_intersect(rayoActual, visto, dist2, materialAux, flotador)){ 
                    if (dist2 > 1e-1){
                        if(abs(dist2) < abs(distanciaHastaLuz)){
                            //std::cout << "Es false porque distancia " << distancia << " y a la luz hay " << distanciaHastaLuz << std::endl;
                            recibeLuz = false;
                        }
                    }
                }
            }
        }
        if (!recibeLuz){
            pixelaux.update(0.0, 0.0, 0.0);
        }
    }

    return pixelaux; 
}



image Sensor::ver(vector<Obstacle*> &entorno, vector<LuzPuntual*> &luces, string imagenNombre, int anchototal, int altoTotal){
    image imagen(imagenNombre, true, anchototal, altoTotal);        
    Emission visto;
    Pixel pixel(visto);
    float aux;
        
    float imageAspectRatio = anchototal / (float)altoTotal; 
    Matrix4x4 cameraToWorld(coordenadasU.c[0], coordenadasI.c[0], apunta.c[0], coordenadasO.c[0], 
                            coordenadasU.c[1], coordenadasI.c[1], apunta.c[1], coordenadasO.c[1],
                            coordenadasU.c[2], coordenadasI.c[2], apunta.c[2], coordenadasO.c[2],
                            0.0, 0.0, 0.0, 1.0);

    for (int miraPixel=0; miraPixel < imagen.total; miraPixel++){
            
        //cout << "loop" << endl;
        int alto=miraPixel/imagen.height;
        int ancho=miraPixel%imagen.height;

        float x = (2 * (alto + 0.5) / (float)anchototal - 1) * imageAspectRatio; 
        float y = (1 - 2 * (ancho + 0.5) / (float)altoTotal); 

        //TODO: cambiar a valor por entrada y generación de array
        float X1 = (float)((rand() % 20)+5)/100;
        float X2 = (float)((rand() % 20)+5)/100;
        float Y1 = (float)((rand() % 20)+5)/100;
        float Y2 = (float)((rand() % 20)+5)/100;

        vector<Ray> rayos; //La array está aquí
        Vectores rayDirection1(x-X1/(float)anchototal, y-Y1/(float)altoTotal, apunta.c[2], 0);
        Ray rayoAux1(this->coordenadasO,rayDirection1); //Generar rayo
        rayoAux1.direccion.traspConMatriz(cameraToWorld);
        rayos.push_back(rayoAux1);
        Vectores rayDirection2(x-X2/(float)anchototal, y+Y1/(float)altoTotal, apunta.c[2], 0);
        Ray rayoAux2(this->coordenadasO,rayDirection2); //Generar rayo
        rayoAux2.direccion.traspConMatriz(cameraToWorld);
        rayos.push_back(rayoAux2);
        Vectores rayDirection3(x+X1/(float)anchototal, y-Y2/(float)altoTotal, apunta.c[2], 0);
        Ray rayoAux3(this->coordenadasO,rayDirection3); //Generar rayo
        rayoAux3.direccion.traspConMatriz(cameraToWorld);
        rayos.push_back(rayoAux3);
        Vectores rayDirection4(x+X2/(float)anchototal, y+Y2/(float)altoTotal, apunta.c[2], 0);
        Ray rayoAux4(this->coordenadasO,rayDirection4); //Generar rayo
        rayoAux4.direccion.traspConMatriz(cameraToWorld);
        rayos.push_back(rayoAux4);


        vector<Pixel> recibidos;
        bool impactado;
        for (auto ray : rayos){
            impactado = false;

            Pixel pixel = colorRayo(ray, entorno, luces, impactado);

            if(impactado){
                recibidos.push_back(pixel);
            }
        }
        
        imagen.imageMatrix[miraPixel]=media(recibidos);
        //cout << imagen.imageMatrix[miraPixel].R << " " <<imagen.imageMatrix[miraPixel].G << " " <<imagen.imageMatrix[miraPixel].B << " " << endl;
        //cout << "endloop" << endl;
    }
    //cout << "TerminaLoop" << endl;
    return imagen;
}