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
    Vectores resultado = (in.restarVector(aux));
    resultado.normalizar();
    return resultado;
}

Vectores refraction(Vectores in, Vectores n, Vectores choque, Obstacle* obstaculo){

    float refraccionExterior = 1.0003F;
    float refraccionObject = obstaculo->getRefractiveIndex();

    float mu = refraccionExterior/refraccionObject;

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

Vectores diffuse(Vectores in, Vectores n, Vectores choque){
    float theta = acos(sqrt(((double) rand() / (RAND_MAX))));   //Inclinacion
    float p = 2.0 * M_PI * ((double) rand() / (RAND_MAX));      //Azimuth

    Vectores resultado = Vectores((sin(theta)*cos(p)), (sin(theta)*sin(p)), cos(theta), 0); 

    Vectores z = n;

    Vectores y = z.ProductoVectorial(in);
    y.normalizar();

    Vectores x = z.ProductoVectorial(y);
    x.normalizar();

    Matrix4x4 matrizCambioBase = Matrix4x4(x.c[0],x.c[1],x.c[2],x.tipoPunto,y.c[0],y.c[1],y.c[2], y.tipoPunto,z.c[0],z.c[1],z.c[2], z.tipoPunto,choque.c[0],choque.c[1],choque.c[2], choque.tipoPunto);
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
    Vectores menorImpacto;
    Material material;
    Emission visto;
    Pixel pixelaux;
    float distancia;
    float menorDistancia = INFINITY;
    Obstacle* obstaculoGolpeado;

    bool noTerminado = true;

    while (noTerminado){
        impactado = false;
        
        for (auto obstacle : entorno){
            Material materialAux;
            Vectores impacto;
            if(obstacle->ray_intersect(ray, visto, distancia, materialAux, impacto)){ 
                impactado = true;
                if(distancia<menorDistancia){
                    menorImpacto = impacto;
                    material = materialAux;
                    pixelaux.update(visto);
                    menorDistancia=distancia;
                    obstaculoGolpeado = obstacle;
                }
            }
        }
        //Tenemos la distancia y el vector de golpe.
        if (impactado){

            if(obstaculoGolpeado->isEmitter()){
                //Fin de rebotes, hemos encontrado fuente de luz
            }else{
                //No es un emisor de luz, por lo que el rayo intentará rebotar

                //Calcular iluminación del punto -> color pixel en rebote actual

                //Obtener evento de rebote (si hay) y calcular nueva direccion

                //Con nueva direccion, realizamos colorRayo(nuevaDirection) para saber el color del resto de pasos

                //Operar con ambos colores para devolver resultado final
            }









            /*
            //Si lo ve una luz puntual, dejar color. Sino negro como nuestro futuro
            Vectores nuevoOrigen;
            nuevoOrigen.calculaPunto(ray.origen, ray.direccion, menorDistancia);

            //Tenemos el punto donde impacta y el vector de luces. Para cada una, mirar si tiene luz

            bool recibeLuz;
            // TODO: Tener en cuenta que obstáculo sea transparente
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
            }*/
            
        }
        else {
            noTerminado = false;
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