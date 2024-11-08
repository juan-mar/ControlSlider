#ifndef STEPPER_H_
#define STEPPER_H_

#include<Arduino.h>
//#include "DRV8825.h"


/*******************************************************************************
 * CONEXION DE PINES
 ******************************************************************************/
#define DIR     26
#define STEP    27
#define EN      25
//#define SLEEP 35

#define HIGH    1
#define LOW     0

//Para el enable, es activo bajo
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
class Motor{
public:
    //Constructor
    Motor(int stepPin, int dirPin, int enPin);

    //Destructor
    ~Motor();


    void calcTraj(int x_o, int x_f, float time);   //Funcion para calcular la velocidad
    void enableMotor(bool en);                      //Funcion para habilitar el motor
    void setDir(bool dir);                          //Funcion para cambiar la direccion
    bool isMoving();                                //Funcion para obtener el estado del motor
    void toggleMove();                              //Funcion para mover el motor


private:
    int stepPin;
    int dirPin;
    int speed;
    int stepsRemainig;
    int enPin;


};



//void InitMotor();

//int calcSpeed(int x_o, int x_f, float time);

//int setDir(bool dir);

//int getEstado();

#endif /* STEPPER_H_ */