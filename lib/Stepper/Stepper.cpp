/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "Stepper.h"
#include "slider.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
 


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
 //static DRV8825 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MODE0, MODE1, MODE2);

typedef struct{
    bool dir;
    float vel;
    float time;
}motor_t;


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
// motor_t stepper;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
    GLOBAL METHODS DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
Motor::Motor(int step, int dir)
{
    pinMode(EN, OUTPUT);
    pinMode(dirPin, OUTPUT);
    stepPin = step;
    pinMode(stepPin, OUTPUT);
    dirPin = dir;
    digitalWrite(EN, ON);
}


Motor::~Motor()
{

}

void Motor::calcTraj(int x_o, int x_f, float time)
{
    int vel;
    int steps = abs(x_f - x_o);
    stepsRemainig = steps;
    if(time)
    {
        vel = (x_f - x_o)/time;             //me da en pasos por segundo
    }
    else
    {
        vel = 0;
    }
    speed = vel;
    vel < 0 ? setDir(ANTIHORARIO) : setDir(HORARIO);
}


void Motor::enableMotor(bool en)
{
    if(en == ON)
    {
        digitalWrite(EN, OFF);
    }
    else
    {
        digitalWrite(EN, ON);
    }
}

void Motor::setDir(bool dir)
{
    digitalWrite(DIR, dir);
}

bool Motor::isMoving()
{
    if(stepsRemainig)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Motor::toggleMove() //cuidado a la mitad de los tiempos tiene que llamarse esta funcion
{
    if(stepPin == LOW)
    {
        digitalWrite(stepPin, HIGH);
    }
    else
    {
        digitalWrite(stepPin, LOW);
    }
}

/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



