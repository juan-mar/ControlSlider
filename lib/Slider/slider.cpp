
#include "slider.h"
#include "Stepper.h"


static Slider slider;


Slider::Slider(){
    numTramos = 1;
    esLoop = false;
    
    distanciasTramos[0][0] = 0;
    distanciasTramos[0][1] = 1;
    
   // std::array<double, 2> tramo = {0, 1};
    //distanciasTramos.push_back(tramo);
    //tiemposTramos.push_back(10);
        tiemposTramos[0] = 10;
}

Slider::~Slider(){

}

void Slider::agregarTramo(double x0, double xf, double tiempo){
    distanciasTramos[numTramos][0] = x0;
    distanciasTramos[numTramos][1] = xf;
    numTramos++;
}


void Slider::borrarUltimoTramo(){
    numTramos--;
}

void Slider::modificarTramo(int tramo, uint64_t x0, uint64_t xf, uint64_t tiempo){
    distanciasTramos[tramo][0] = x0;
    distanciasTramos[tramo][1] = xf;
    tiemposTramos[tramo] = tiempo;
}

uint64_t Slider::getX0(int tramo){
    return distanciasTramos[tramo][0];
}

uint64_t Slider::getXf(int tramo){
    //return distanciasTramos[tramo][1];
    return distanciasTramos[tramo][1];
}

uint64_t Slider::getTiempo(int tramo){
    return tiemposTramos[tramo];
}

