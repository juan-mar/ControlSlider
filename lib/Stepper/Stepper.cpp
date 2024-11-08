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
Motor::Motor(int step, int dir, int en)
{
    pinMode(en, OUTPUT);
    enPin = en;
    pinMode(dirPin, OUTPUT);
    stepPin = step;
    pinMode(stepPin, OUTPUT);
    dirPin = dir;
    digitalWrite(enPin, ON);
    setDir(HORARIO);
}


Motor::~Motor()
{

}

void Motor::calcTraj(int x_o, int x_f, float time)
{
    stepsRemainig = abs(x_f - x_o);
    speed = stepsRemainig/(time*1000);                     //me da en pasos por ms
    x_f < x_o ? setDir(ANTIHORARIO) : setDir(HORARIO);
    timeConst = 1000 * time/stepsRemainig;                 //tiempo entre pasos en ms
}


void Motor::enableMotor(bool en)
{
    if(en == ON)
    {
        digitalWrite(enPin, OFF);
    }
    else
    {
        digitalWrite(enPin, ON);
    }
}

void Motor::setDir(bool dir)
{
    digitalWrite(dirPin, dir);
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

int Motor::getTimeConst()
{
    return timeConst;
}

/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



