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



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


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

    pinMode(step, OUTPUT);
    stepPin = step;
    
    pinMode(dir, OUTPUT);
    dirPin = dir;
    
    digitalWrite(enPin, ON);
    digitalWrite(dirPin, HIGH);

    stepsCurrent = 0;
   
}


Motor::~Motor()
{

}

void Motor::calcConstTime(int x_o, int x_f, float time)
{
    stepsRemainig = abs(x_f - x_o);
    speed = stepsRemainig/(time*1000);                     //me da en pasos por ms
    timeConst = (1000*1000 * time)/stepsRemainig;                 //tiempo entre pasos en MICROS
}


void Motor::setEnableMotor(int en)
{
    digitalWrite(enPin, en);
    isEnableMotor = en;
}

void Motor::setDir(int dir_)
{
    digitalWrite(dirPin, dir_);
}

void Motor::setMoreSteps(uint64_t steps)
{
    stepsRemainig += steps;
}

void Motor::setStepsRem(uint64_t steps)
{
    stepsRemainig = steps;
}

void Motor::setTimeConst(uint64_t time)
{
    timeConst = time;
}   


void Motor::setStepCurrent(int64_t step)
{
    stepsCurrent = step;
}

int Motor::getDir()
{
    return digitalRead(dirPin);
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

void Motor::sendStep() //cuidado a la mitad de los tiempos tiene que llamarse esta funcion
{
    //digitalWrite(stepPin, !digitalRead(stepPin));
    if( digitalRead(stepPin) == LOW)
    {
        stepsRemainig--;
        if(digitalRead(dirPin) == HORARIO){
            stepsCurrent--;
        }
        else{
            stepsCurrent++;
        }
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

uint64_t Motor::getStepsRemainig(){
    return stepsRemainig;
}

bool Motor::getEnableMotor()
{
    return isEnableMotor;
}

uint64_t Motor::getStepCurr()
{
    return stepsCurrent;
}
/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



