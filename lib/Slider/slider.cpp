
#include "slider.h"

Slider::Slider(){

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