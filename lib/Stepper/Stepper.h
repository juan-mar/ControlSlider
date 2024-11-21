#ifndef STEPPER_H_
#define STEPPER_H_

#include<Arduino.h>


/*******************************************************************************
 * CONEXION DE PINES
 ******************************************************************************/

#define HIGH    1
#define LOW     0

//Para el enable, es activo bajo
#define ON      0
#define OFF     1

#define MAX_PARTS   5

#define MAX_VEL     1000

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

    bool isMoving();                                        //Funcion para obtener el estado del motor
    void calcConstTime(int x_o, int x_f, float time);       //Funcion para calcular la velocidad
    void setEnableMotor(int en);                            //Funcion para habilitar el motor
    void setDir(int dir);                                   //Funcion para cambiar la direccion
    void setMoreSteps(uint64_t steps);                      //Funcion para agregar pasos
    void setStepsRem(uint64_t steps);                          //Funcion para setear pasos
    void setTimeConst(uint64_t time);                       //Funcion para setear la constante de tiempo
    void setStepCurrent(int64_t step);

    int getDir();
    bool getEnableMotor();                                  //Funcion para obtener la direccion
    int getTimeConst();  
    uint64_t getStepsRemainig();
    uint64_t getStepCurr();                          //Funcion para obtener la constante de tiempo
    
    void sendStep();                              //Funcion para mover el motor
    

private:
    int stepPin;
    int dirPin;
    int speed;
    int stepsRemainig;
    int enPin;
    int timeConst;
    int isEnableMotor;
    int64_t stepsCurrent;

};



//void InitMotor();

//int calcSpeed(int x_o, int x_f, float time);

//int setDir(bool dir);

//int getEstado();

#endif /* STEPPER_H_ */