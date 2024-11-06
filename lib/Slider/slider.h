#ifndef SLIDER_H
#define SLIDER_H

#include <vector>
#include <array>

class Slider {
public:
    // Public attributes
    int numTramos;
    bool esLoop;

    // Constructor
    Slider();
        
    // Destructor
    ~Slider();


    void agregarTramo(double x0, double xf, double tiempo = 10);
    void borrarTramo(int tramo);
    void borrarUltimoTramo();
    void modificarTramo(int tramo, double x0, double xf, double tiempo = 10);
    

    //Funcion para leer la distancia de un tramo
    double getX0(int tramo);
    double getXf(int tramo);
    //Funcion para leer el tiempo del tramo 
    double getTiempo(int tramo);

private:
    std::vector<std::array<double, 2>> distanciasTramos;
    std::vector<double> tiemposTramos;
   
};

#endif // SLIDER_H