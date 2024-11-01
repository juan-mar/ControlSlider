#ifndef STEPPER_H_
#define STEPPER_H_

#include<Arduino.h>
#include "DRV8825.h"


/*******************************************************************************
 * CONEXION DE PINES
 ******************************************************************************/
#define DIR 26
#define STEP 27
#define SLEEP 35

#define MODE0 10
 #define MODE1 11
 #define MODE2 12

 /*******************************************************************************
 * DEFINICION DE CONSTANTES
 ******************************************************************************/
#define MOTOR_STEPS 200

#define RPM 120

#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

#define MICROSTEPS 32

/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
void InitMotor();

void setMove(int vel, bool sentido);

#endif /* STEPPER_H_ */