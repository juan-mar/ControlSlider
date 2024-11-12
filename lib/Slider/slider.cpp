
#include "slider.h"
#include "Stepper.h"

static Slider slider;

Slider::Slider(){
    numTramos = 1;
    esLoop = false;
    std::array<double, 2> tramo = {0, 1};
    distanciasTramos.push_back(tramo);
    tiemposTramos.push_back(10);
        
}

Slider::~Slider(){

}

void Slider::agregarTramo(double x0, double xf, double tiempo){
    std::array<double, 2> tramo = {x0, xf};
    distanciasTramos.push_back(tramo);
    tiemposTramos.push_back(tiempo);
    numTramos++;
}

void Slider::borrarTramo(int tramo){
    distanciasTramos.erase(distanciasTramos.begin() + tramo);
    tiemposTramos.erase(tiemposTramos.begin() + tramo);
    numTramos--;
}

void Slider::borrarUltimoTramo(){
    distanciasTramos.pop_back();
    tiemposTramos.pop_back();
    numTramos--;
}

void Slider::modificarTramo(int tramo, double x0, double xf, double tiempo){
    distanciasTramos[tramo][0] = x0;
    distanciasTramos[tramo][1] = xf;
    tiemposTramos[tramo] = tiempo;
}

double Slider::getX0(int tramo){
    return distanciasTramos[tramo][0];
}

double Slider::getXf(int tramo){
    return distanciasTramos[tramo][1];
}

double Slider::getTiempo(int tramo){
    return tiemposTramos[tramo];
}

