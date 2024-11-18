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
#define STOPPED 0
#define RUNNING 1
#define PAUSED  2

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

int getCantTramos();                                                        //Devuelve la cantidad de tramos

void setState(int estado);                                                  //Setea el flag de inicio de movimiento

int getStateSlider();                                                       //Indica el estado actual del slider

uint64_t getXf(int tramo);                                                  //Devuelve la posicion final de un tramo

int getCurrentTramo();



//Funciones para Motor
void move2origin(Button * inicioLinea);                                     //Mueve el motor a x0

void updateMotor();                                                         //se llama desde el main para mover al motor

void setTimeConst(uint64_t time);                                           //Setea la constante de tiempo

void runMotor();                                                            //Mueve el motor

void setMotorDir(int dir);

void setMotorEnable(int enable);

void setMoreSteps(int step);

uint64_t getCurrStep();

int getMotorDir();

bool getEnableMotor();

void setStepRemainig(int step);

uint64_t getStepRemainig();

void setStepCurrent(uint64_t step);

uint64_t getStepCurrent();


#endif /* SLIDERCAMARA_H_ */