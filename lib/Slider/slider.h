#ifndef SLIDER_H
#define SLIDER_H

#include <vector>
#include <array>

class Slider {
public:
    // Public attributes
    int numTramos;
    bool esLoop;
    uint64_t maxPasos;

    // Constructor
    Slider();
        
    // Destructor
    ~Slider();


    void agregarTramo(double x0, double xf, double tiempo = 10);
    void borrarUltimoTramo();
    void modificarTramo(int tramo, uint64_t x0, uint64_t xf, uint64_t tiempo);
    void setMaxPasos(uint64_t pasos);
    

    //Funcion para leer la distancia de un tramo
    uint64_t getX0(int tramo);
    uint64_t getXf(int tramo);
    //Funcion para leer el tiempo del tramo 
    uint64_t getTiempo(int tramo);
    uint64_t getMaxPasos();

private:
    uint64_t distanciasTramos[5][2];
//    std::vector<std::array<double, 2>> distanciasTramos;
    uint64_t tiemposTramos[5];    
//    std::vector<double> tiemposTramos;
   
};


// Function to get the slider
Slider * get_slider();


#endif // SLIDER_H