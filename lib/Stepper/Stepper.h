#ifndef STEPPER_H_
#define STEPPER_H_

#include<Arduino.h>
#include "DRV8825.h"


/*******************************************************************************
 * CONEXION DE PINES
 ******************************************************************************/
#define DIR     26
#define STEP    27
#define EN      25
//#define SLEEP 35

#define HIGH    1
#define LOW     0
#define ON      0
#define OFF     1

#define MAX_PARTS   5

 /*******************************************************************************
 * DEFINICION DE CONSTANTES
 ******************************************************************************/

#define MICROSTEPS  32

#define HORARIO     1
#define ANTIHORARIO 0

/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
void InitMotor();

int calcSpeed(int x_o, int x_f, float time);

int setDir(bool dir);

int getEstado();

#endif /* STEPPER_H_ */