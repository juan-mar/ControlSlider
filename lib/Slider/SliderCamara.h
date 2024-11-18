#ifndef SLIDERCAMARA_H_
#define SLIDERCAMARA_H_


#include <Arduino.h>
#include <stdint.h>
#include "Button.h"

/*******************************************************************************
 * DEFINICION DE CONSTANTES
 ******************************************************************************/



/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
void storeMovement(uint64_t x0, uint64_t xf, uint64_t tiempo);

void move2origin(Button * inicioLinea);

void updateMotor();

void setTimeConst(uint64_t time);

void runMotor();

void setMotorDir(int dir);

void setMotorEnable(int enable);

void setMotorSteps(int step);

void getCurrStep();

void getEnableMotor();






#endif /* SLIDERCAMARA_H_ */