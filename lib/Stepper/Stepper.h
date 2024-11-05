#ifndef STEPPER_H_
#define STEPPER_H_

#include<Arduino.h>
#include "DRV8825.h"


/*******************************************************************************
 * CONEXION DE PINES
 ******************************************************************************/
#define DIR 26
#define STEP 27
//#define SLEEP 35

#define HIGH    1
#define LOW     0

 /*******************************************************************************
 * DEFINICION DE CONSTANTES
 ******************************************************************************/
#define MOTOR_STEPS 200

//#define RPM 120

#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

#define MICROSTEPS  32

#define HORARIO     1
#define ANTIHORARIO 0

/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
void InitMotor();

int calcSpeed(int x_o, int x_f, float time);

void setMove(float vel, bool dir);

#endif /* STEPPER_H_ */