#pragma once

#include "sensor.hpp"
#include "vector.cpp"
#include "ray.cpp"

#include <cmath>
#include <chrono>

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
    REFRACTION,     // Translucido
    DIFFUSE,        // Turbio, plasticoso
    SPECULAR,       // Espejito espejito
    DEAD            
};


EVENT getRandomEvent(const Material &material) {
    // Russian roulette

    float Kd = material.kd;
    float Ks = material.ks;
    float Krefraction = material.krefraction;

    // Max value limit
    const float MAX = 0.95f;
    float sum = Kd + Ks + Krefraction;
    if (sum > MAX) {
        Kd *= MAX / sum;
        Ks *= MAX / sum;
        Krefraction *= MAX / sum;
    }

    float randomZTO = ((double) rand() / (RAND_MAX));

    if ((randomZTO -= Kd) < 0) {
        // DIFFUSE case
        return DIFFUSE;
    } else if ((randomZTO -= Ks) < 0) {
        // SPECULAR case 
        return SPECULAR;
    } else if ((randomZTO -= Krefraction) < 0) {
        // REFRACTION case
        return REFRACTION;
    } else {
        // DEAD case
        return DEAD;
    }
}

Vectores reflect(Vectores in, Vectores n) { //n is the normal of the surface (mirror), in is the received vector
    Vectores aux = n.multiplicarValor(in.punto(n));
    aux.multiplicarValor(2.0);
    Vectores resultado = (aux.restarVector(in));
    resultado.normalizar();
    return resultado;
}

Vectores refraction(Vectores in, Vectores n, Vectores choque, Obstacle* obstaculo){

    float refraccionExterior = 1.0003F;
    float refraccionObject = obstaculo->getRefractiveIndex();

    float mu = refraccionExterior/(refraccionObject+0.01);

    Vectores normal = n;
    Vectores externa = in;
    float cosExterior = - externa.punto(normal); //help
    float k = 1.0 - mu*mu * (1- cosExterior*cosExterior);

    Vectores interior;
    if(k<0){
        interior = externa;
    }else{
        interior = (externa.multiplicarValor(mu)).sumarVector(normal.multiplicarValor(mu*cosExterior-sqrt(k))); //help
    }

    //SegundaInteraccion

    Ray rayoInterno = Ray (choque, interior);
    Emission emisorAux;
    float distanciaAux;
    Vectores normalGolpe;
    Material materialAux;
    obstaculo->ray_intersect(rayoInterno, emisorAux, distanciaAux, materialAux, normalGolpe); 

    normal = normalGolpe;
    externa = rayoInterno.direccion;
    cosExterior = - externa.punto(normal);
    k = 1.0 - mu * mu * (1- cosExterior*cosExterior);
    
    Vectores resultado;
    if(k<0){
        resultado = normal.cruce(externa);
    }
    else{
        resultado = (externa.multiplicarValor(mu)).sumarVector(normal.multiplicarValor(mu*cosExterior-sqrt(k)));
    }

    return resultado;
} 

//    static unsigned seed = chrono::system_clock::now().time_since_epoch().count();;
//    default_random_engine generator (seed);
//    uniform_real_distribution<float> rd (0.0,1.0);

//float rand_f(float min, float max) {
//    return rd(generator);;
//}

Vectores diffuse(Vectores in, Vectores n, Vectores choque){
    //eo = rand_f(0,1);
    float theta = acos(sqrt(((double) rand() / (RAND_MAX))));   //Inclinacion
    float p = 2.0 * M_PI * ((double) rand() / (RAND_MAX));      //Azimuth

    Vectores resultado = Vectores((sin(theta)*cos(p)), (sin(theta)*sin(p)), cos(theta), 0); 

    Vectores z = n;
    z.normalizar();

    Vectores aux = Vectores(n.c[0]+24, n.c[1]+48 , n.c[2], 0);
    //Vectores aux = n;
    //aux.normalizar();
    Vectores y = z.ProductoVectorial(aux);
    y.normalizar();

    Vectores x = z.ProductoVectorial(y);
    x.normalizar();

    Vectores choque_ = choque;

    //Matrix4x4 matrizCambioBase = Matrix4x4(x.c[0],x.c[1],x.c[2],x.tipoPunto,y.c[0],y.c[1],y.c[2], y.tipoPunto,z.c[0],z.c[1],z.c[2], z.tipoPunto,choque_.c[0],choque_.c[1],choque_.c[2], choque_.tipoPunto);
    Matrix4x4 matrizCambioBase = Matrix4x4( x.c[0], y.c[0], z.c[0], choque_.c[0], x.c[1], y.c[1], z.c[1], choque_.c[1], x.c[2], y.c[2], z.c[2], choque_.c[2], 0, 0, 0, 1);
    resultado.traspConMatriz(matrizCambioBase);

    resultado.normalizar();
    return resultado;
}

Vectores generarDireccion(EVENT e, Vectores in, Vectores n, Vectores choque, Obstacle *obstaculo){
    switch (e)
    {
    case REFRACTION:
        return refraction(in, n, choque, obstaculo);
        break;

    case DIFFUSE:
        return diffuse(in, n, choque);
        break;

    case SPECULAR:
        return reflect(in, n);
        break;

    case DEAD:
        return Vectores(0.0, 0.0, 0.0, 0);      //Vector nulo
        break;
        
    default:
        return Vectores(0.0, 0.0, 0.0, 0);      //Vector nulo
        break;
    }
}


Pixel Sensor::colorRayo(Ray ray, vector<Obstacle*> &entorno, vector<LuzPuntual*> &luces, bool &impactado){
    Vectores normalGolpe;
    Material material;
    Emission visto;
    Pixel pixelaux;
    float distancia;
    impactado = false;
    float menorDistancia = INFINITY;
    Obstacle* obstaculoGolpeado;
    int numRebotes = 0;

    Emission luzActual = Emission(1, 1, 1);
    Emission vistoCercano;

    bool continuarCamino = true;
    bool impactadoInterno = false;

    while (continuarCamino){
        
        impactadoInterno = false;
        float menorDistancia = INFINITY;
        
        for (auto obstacle : entorno){
            Material materialAux;
            Vectores impacto;
            if(obstacle->ray_intersect(ray, visto, distancia, materialAux, impacto)){ 
                impactado = true;
                if(distancia<menorDistancia){
                    normalGolpe = impacto;
                    material = materialAux;
                    pixelaux.update(visto);
                    vistoCercano = visto;
                    menorDistancia=distancia;
                    obstaculoGolpeado = obstacle;
                    impactadoInterno = true;
                }
            }
        }
        //Tenemos la distancia y el vector de golpe.
        if (impactadoInterno){

            if(obstaculoGolpeado->getMaterial().isEmissor()){
                luzActual = luzActual * vistoCercano;
                continuarCamino = false;
            }else{

                EVENT e = getRandomEvent(material);
                if (e == DEAD){
                    //luzActual = Emission(0,0,0);
                    continuarCamino = false;
                }
                else {      //Cosas que hacer con el evento...
                    //No es un emisor de luz, por lo que el rayo intentará rebotar

                    //Calcular iluminación del punto -> color pixel en rebote actual
                    if (e == SPECULAR){
                        luzActual = luzActual /*+ (vistoCercano * 0.1)*/;
                    }else if (e == REFRACTION){
                        luzActual = luzActual * vistoCercano;
                        //continuarCamino = false;
                    }else{
                        luzActual = luzActual * vistoCercano;
                        /*if(obstaculoGolpeado->queSoy()=="esfera"){
                            continuarCamino = false;
                            luzActual = vistoCercano;
                        }*/
                    }

                    Vectores nuevoOrigen = ray.origen.sumarVector(ray.direccion.multiplicarValor(menorDistancia));

                    //Tenemos el punto donde impacta y el vector de luces. Para cada una, mirar si tiene luz

                    bool recibeLuz;
                    // TODO: Tener en cuenta que obstáculo sea transparente
                    for (auto luz : luces){
                        
                        recibeLuz = true;

                        //Sacamos la línea (rayo) entre el impacto y la luz "luz"

                        //Sumar el origen
                        /*
                        Vectores vectorEntreImpactoYLuz=luz->coordenada;
                        nuevoOrigen.VectorDosPuntos(vectorEntreImpactoYLuz);
                        vectorEntreImpactoYLuz.normalizar();*/
                        
                        Vectores vectorEntreImpactoYLuz=luz->coordenada;

                        //Vectores vOrigen = nuevoOrigen;
                        Vectores aux32 = vectorEntreImpactoYLuz.VectorDosPuntos(nuevoOrigen);
                        //vectorEntreImpactoYLuz = vOrigen;
                        aux32.normalizar();

                        //Cogemos la distancia entre ambos puntos, para compararla con la distancia a obstáculos
                        float distanciaHastaLuz = vectorEntreImpactoYLuz.distDosPuntos(nuevoOrigen) / ray.direccion.distAbsoluta();
                        
                        Ray rayoActual = Ray(nuevoOrigen,aux32);
                        for (auto obstacle : entorno){
                            Material materialAux;
                            Vectores flotador3;
                            float dist2;
                            if(obstacle->ray_intersect(rayoActual, visto, dist2, materialAux, flotador3)){ 
                                if (dist2 > 1e-1){
                                    if(dist2 < distanciaHastaLuz){
                                        //std::cout << "Es false porque distancia " << distancia << " y a la luz hay " << distanciaHastaLuz << std::endl;
                                        recibeLuz = false;
                                    }
                                }
                            }
                        }
                    }
                    if (!recibeLuz){
                        luzActual = luzActual * 0.2;
                        //continuarCamino = false;
                    }


                    //Obtener evento de rebote (si hay) y calcular nueva direccion
                    // Vectores puntoDeGolpe = calculaPunto(ray.origen,ray.direccion,menorDistancia);
                    Vectores puntoDeGolpe = ray.origen.sumarVector(ray.direccion.multiplicarValor(menorDistancia));

                    Vectores nuevaDireccion = generarDireccion(e, ray.direccion, puntoDeGolpe, normalGolpe, obstaculoGolpeado);
                    Vectores nuevoLugar = puntoDeGolpe;

                    //Con nueva direccion, realizamos colorRayo(nuevaDirection) para saber el color del resto de pasos
                    ray = Ray(nuevoLugar, nuevaDireccion);

                    numRebotes++;
                }


            }









            /*
            //Si lo ve una luz puntual, dejar color. Sino negro como nuestro futuro
            Vectores nuevoOrigen = calculaPunto(ray.origen, ray.direccion, menorDistancia);

            //Tenemos el punto donde impacta y el vector de luces. Para cada una, mirar si tiene luz

            bool recibeLuz;
            // TODO: Tener en cuenta que obstáculo sea transparente
            for (auto luz : luces){
                
                recibeLuz = true;

                //Sacamos la línea (rayo) entre el impacto y la luz "luz"

                //Sumar el origen
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
            }*/
            
        }else {
            continuarCamino = false;
        }
    }

    luzActual = luzActual;
    pixelaux.update(luzActual);
    return pixelaux; 
}



image Sensor::ver(vector<Obstacle*> &entorno, vector<LuzPuntual*> &luces, string imagenNombre, int anchototal, int altoTotal, int ppp){
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

        float x = (2 * (alto) / (float)anchototal - 1) * imageAspectRatio; 
        float y = (1 - 2 * (ancho) / (float)altoTotal);

        vector<Ray> rayos; //La array está aquí

        Emission totalEmission = Emission(0.0, 0.0, 0.0);
        for (int i=0;i<ppp;i++){
            float X = (float)((rand() % 90)+5)/100;
            float Y = (float)((rand() % 90)+5)/100;
            Vectores rayDirection(x+X/(float)anchototal, y+Y/(float)altoTotal, apunta.c[2], 0);
            Ray rayoAux(this->coordenadasO,rayDirection); //Generar rayo
            rayoAux.direccion.traspConMatriz(cameraToWorld);
            rayos.push_back(rayoAux);
        }

        vector<Pixel> recibidos;
        bool impactado;
        for (auto ray : rayos){
            impactado = false;

            Pixel pixel = colorRayo(ray, entorno, luces, impactado);

            //if(impactado){
            //    recibidos.push_back(pixel);
            //}
            totalEmission = Emission(totalEmission.red + pixel.R, totalEmission.green + pixel.G, totalEmission.blue + pixel.B);
        }

        totalEmission = Emission(min(totalEmission.red/ppp, 1.0f), min(totalEmission.green/ppp, 1.0f), min(totalEmission.blue/ppp, 1.0f));

        imagen.imageMatrix[miraPixel] = Pixel(totalEmission);
        //imagen.imageMatrix[miraPixel]=media(recibidos);

        //cout << imagen.imageMatrix[miraPixel].R << " " <<imagen.imageMatrix[miraPixel].G << " " <<imagen.imageMatrix[miraPixel].B << " " << endl;
        //cout << "endloop" << endl;
    }
    //cout << "TerminaLoop" << endl;
    return imagen;
}