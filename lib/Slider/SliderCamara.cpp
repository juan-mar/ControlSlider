/*******************************************************************************
 * @file SliderCamara.cpp
 * @brief Implementation of the Slider Camera control functions.
 * 
 * This file contains the implementation of the functions used to control the 
 * slider camera mechanism. It includes the necessary headers and defines 
 * constants and macros used throughout the code.
 * 
 * @author [Your Name]
 * @date [Date]
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "SliderCamara.h"
#include "slider.h"
#include "Stepper.h"
#include "board.h"
#include "Display.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
static Slider slider;
static Motor stepper;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
uint64_t timer_2 = 0;

/*******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************/
void storeMovement(uint64_t x0, uint64_t xf, uint64_t tiempo)
{
    slider.agregarTramo(x0, xf, tiempo);
}



void move2origin(Button * inicioLinea)
{
    static int go_origin = 1;
    static int go_X0 = 0;

    if(go_origin){
        show_screen("Yendo a inicio", "Moviendo motor");
        stepper.setDir(HORARIO);
        stepper.setEnableMotor(ON);
        if(inicioLinea-> getState()  == NOT_PRESSED){
            stepper.setTimeConst(1000/2);
        }
        else{
            delay(500);
            go_origin = 0;
            go_X0 = 1;
            stepper.setStepCurrent(0);
        }

    }
    
        //stepper.setEnableMotor(ON);
    if(go_X0){
        stepper.setDir(ANTIHORARIO);
        uint64_t x0_ = slider.getX0(0);
        show_screen("Yendo a x0", "Moviendo motor");

        //Go to Initial Position
        if(stepper.getStepCurr() < x0_){
            stepper.setTimeConst(1000/2);
        }
        else{
            delay(500);
            go_X0 = 0;
            go_origin = 0;
        }
        
    }
}

void updateMotor()
{
    if(micros() - timer_2 > (stepper.getTimeConst())){
        stepper.sendStep();
        timer_2 = micros();
    }
}

void setTimeConst(uint64_t time)
{
    stepper.setTimeConst(time);
}

void runMotor()
{
    static int tramos_faltantes = slider.numTramos;
    static int currentTramo = 0;
    static int cantTramos = slider.numTramos;
    static int newTramo = 1;
    if(newTramo){   
        //Estoy en tramo current
        show_screen("Moviendo motor", BLANK);
        stepper.calcTraj(slider.getX0(currentTramo), slider.getXf(currentTramo), 
                                        slider.getTiempo(currentTramo));
    }    
    if(stepper.getStepCurr() < slider.getXf(currentTramo) ){
//    if(stepper.getStepsRemainig()){
        newTramo = 0;
    }
    else{
        //Estoy en tramo siguiente
        currentTramo++;
        newTramo = 1;
    }
    
    if(micros() - timer_2 > (stepper.getTimeConst()/2)){
        if(stepper.getStepCurr() < slider.getXf(currentTramo)){
            stepper.sendStep();
        }
        else{
            stepper.setEnableMotor(OFF);
        }
        timer_2 = micros();
    }
}


void setMotorDir(int dir)
{
    stepper.setDir(dir);
}

void setMotorEnable(int enable)
{
    stepper.setEnableMotor(enable);
}

void setMotorSteps(int step)
{
    stepper.setMoreSteps(step);
}

void getCurrStep()
{
    stepper.getStepCurr();
}

void getEnableMotor()
{
    stepper.getEnableMotor();
}