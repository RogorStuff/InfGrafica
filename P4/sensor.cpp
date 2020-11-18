#include "sensor.hpp"
#include "pixel.cpp"

Sensor::Sensor(){

}

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

Image Sensor::ver(vector<Obstacle*> &entorno, string imagenNombre, int anchototal, int altoTotal){
    Image imagen(imagenNombre, true, anchototal, altoTotal);        
    Emission visto;
    Pixel pixel(visto);
    float aux;
        
    float imageAspectRatio = anchototal / (float)altoTotal; 
    Matrix4x4 cameraToWorld(coordenadasU.c[0], coordenadasI.c[0], apunta.c[0], coordenadasO.c[0], 
                            coordenadasU.c[1], coordenadasI.c[1], apunta.c[1], coordenadasO.c[1],
                            coordenadasU.c[2], coordenadasI.c[2], apunta.c[2], coordenadasO.c[2],
                            0.0, 0.0, 0.0, 1.0);

    for (int miraPixel=0; miraPixel < imagen.total; miraPixel++){
            
        int alto=miraPixel/imagen.height;
        int ancho=miraPixel%imagen.height;

        float x = (2 * (alto + 0.5) / (float)anchototal - 1) * imageAspectRatio; 
        float y = (1 - 2 * (ancho + 0.5) / (float)altoTotal); 

        //Vectores rayDirection(x, y, apunta.c[2], 0);
        //Ray rayoAux(this->coordenadasO,rayDirection); //Generar rayo
        //rayoAux.direccion.traspConMatriz(cameraToWorld);

        float X1 = (float)((rand() % 20)+5)/100;
        float X2 = (float)((rand() % 20)+5)/100;
        float Y1 = (float)((rand() % 20)+5)/100;
        float Y2 = (float)((rand() % 20)+5)/100;
        vector<Ray> rayos;
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
        for (auto ray : rayos){
            float menorDistancia=1000000.0;
            bool impactado =false;
            for (auto obstacle : entorno){
                if(obstacle->ray_intersect(ray,visto,aux)){ 
                    impactado = true;
                    if(aux<menorDistancia){
                        pixel.update(visto);
                        menorDistancia=aux;
                    }
                }
            }
            if(impactado){
                recibidos.push_back(pixel);
            }
        }
        if (recibidos.size()>0){
            imagen.imageMatrix[miraPixel]=media(recibidos);
        }
    }
    return imagen;
}