#ifndef SLIDERCAMARA_H_
#define SLIDERCAMARA_H_


#include <Arduino.h>
#include <stdint.h>
#include "Button.h"
#include "Stepper.h"
#include "slider.h"

/*******************************************************************************
 * DEFINICION DE CONSTANTES
 ******************************************************************************/

enum states_slider{
    STOPPED,
    START,
    RUNNING,
    PAUSED,
    SETTING_MOTOR,
    FINISHED
};

#define ADD     1
#define ERASE   0


/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
//Init
void InitSlider();


//Funciones para Slider
void storeMovement(uint64_t x0, uint64_t xf, uint64_t tiempo);              //Guarda un movimiento en el slider

void modifyMovement(int tramo, uint64_t x0, uint64_t xf, uint64_t tiempo);  //Modifica un movimiento en el slider

void modifyNumTramos(bool action);                                          //Modifica la cantidad de tramos

//Getters
int getCantTramos();                                                        //Devuelve la cantidad de tramos

int getStateSlider();                                                       //Indica el estado actual del slider

uint64_t getXf(int tramo);                                                  //Devuelve la posicion final de un tramo

uint64_t getX0(int tramo);                                                  //Devuelve la posicion inicial de un tramo

int getCurrentTramo();

uint64_t getMaxPasos();

//Setters
void setMaxPasos(uint64_t pasos);

void setState(int estado);                                                  //Setea el flag de inicio de movimiento

int pasos2cm(uint64_t pasos);                                           //Convierte pasos a cm


//Funciones para Motor
void move2origin(Button * inicioLinea);                                     //Mueve el motor a x0

void updateMotor();                                                         //se llama desde el main para mover al motor

void runMotor();                                                            //Mueve el motor

//Setters
void setTimeConst(uint64_t time);                                           //Setea la constante de tiempo

void setMotorDir(int dir);

void setMotorEnable(int enable);

void setMoreSteps(int step);

void setStepRemaining(int step);

void setStepCurrent(uint64_t step);

//Getters
uint64_t getCurrStep();

int getMotorDir();

bool getEnableMotor();

uint64_t getStepRemaining();

uint64_t getStepCurrent();


#endif /* SLIDERCAMARA_H_ */