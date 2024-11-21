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
#include "board.h"
#include "Display.h"
#include "EventGenerator.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
static Slider slider;
static Motor stepper = Motor(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);




/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint64_t timer_2 = 0;
static int state;
static int currentTramo;
static int go_origin = 1;
static int go_X0 = 0;

/*******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************/
void InitSlider()
{
    state = STOPPED;
    slider.numTramos = 1;
    currentTramo = 0;
    setStepCurrent(0);
    setMotorEnable(OFF);
}

/*******************************************************************************
 * Slider Functions
 ******************************************************************************/
void storeMovement(uint64_t x0, uint64_t xf, uint64_t tiempo)
{
    slider.agregarTramo(x0, xf, tiempo);
}

void modifyMovement(int tramo, uint64_t x0, uint64_t xf, uint64_t tiempo)
{
    slider.modificarTramo(tramo, x0, xf, tiempo);
}

void modifyNumTramos(bool action)
{
    if(action && slider.numTramos < 5)
    {
        slider.numTramos++;
    }
    else if( action == ERASE && slider.numTramos > 1)
    {
        slider.numTramos--;
    }
}

int getCantTramos()
{
    return slider.numTramos;
}

uint64_t getMaxPasos()
{
    return slider.getMaxPasos();
}

void setMaxPasos(uint64_t pasos)
{
    slider.setMaxPasos(pasos);
}

void setState(int estado)
{
    state = estado;
}

int getStateSlider()
{
    return state;
}

uint64_t getXf(int tramo)
{
    return slider.getXf(tramo);
}

int getCurrentTramo()
{
    return currentTramo;
}

int pasos2cmSlider(uint64_t pasos)
{
    int dist = (float)pasos*75.0/(float)slider.maxPasos;
    return dist;
}


/*******************************************************************************
 * Motor Functions
 ******************************************************************************/
void move2origin(Button * inicioLinea)
{
    static bool show_one_time = true;
    if(go_origin){
        if(show_one_time){
            show_screen("Yendo a inicio", "Moviendo motor");
            show_one_time = false;
        }
        if(inicioLinea-> getState()  == NOT_PRESSED){
            stepper.setTimeConst(1000/2);
            stepper.setDir(HORARIO);
            stepper.setEnableMotor(ON);
            updateMotor();
        }
        else{
            stepper.setStepCurrent(0);
            delay(500);
            go_origin = 0;
            go_X0 = 1;
            show_one_time = true;
        }
    }
    
    //stepper.setEnableMotor(ON);
    if(go_X0){
        stepper.setDir(ANTIHORARIO);
        uint64_t x0_ = slider.getX0(0);
        if(show_one_time){
            show_screen("Yendo a x0", "Moviendo motor");
            show_one_time = false;
        }
        //Go to Initial Position
        if(stepper.getStepCurr() < x0_){
            stepper.setTimeConst(1000/2);
        }
        else{
            delay(500);
            go_X0 = 0;
            go_origin = 1;
            setState(RUNNING);
            EG_addExternEvent(NONE);
            show_one_time = true;
        }
        if (stepper.getStepCurr() < slider.getX0(currentTramo)) {
            updateMotor();
        }
    }
}

void updateMotor()
{
    if(micros() - timer_2 > (stepper.getTimeConst()/2)){
        stepper.sendStep();
        timer_2 = micros();
    }
    //Serial.println(getStepCurrent());
}

void setTimeConst(uint64_t time)
{
    stepper.setTimeConst(time);
}

void runMotor()
{
    static int newTramo = 1;
    if(newTramo){   
        //Estoy en tramo current
        stepper.calcConstTime(slider.getX0(currentTramo), slider.getXf(currentTramo), 
                                        slider.getTiempo(currentTramo));
        newTramo = 0;
    }

    if(slider.getX0(currentTramo) < slider.getXf(currentTramo)){
        stepper.setDir(ANTIHORARIO);
    }
    else{
        stepper.setDir(HORARIO);
    }

    if(stepper.getStepCurr() < slider.getXf(currentTramo) ){
        newTramo = 0;
        updateMotor();
    }
    else{
        //Tramo finalizado
        if(currentTramo < slider.numTramos-1){
            //Si quedan tramos, sigo
            currentTramo++;
            newTramo = 1;
        }
        else{
            //Si no quedan tramos, finalizo
            setState(FINISHED);
            currentTramo = 0;
            newTramo = 1;
        }
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

void setMoreSteps(int step)
{
    stepper.setMoreSteps(step);
}

uint64_t getCurrStep()
{
    return stepper.getStepCurr();
}

bool getEnableMotor()
{
    return stepper.getEnableMotor();
}

void setStepRemaining(int step)
{
    stepper.setStepsRem(step);
}

uint64_t getStepRemaining()
{
    return stepper.getStepsRemainig();
}

void setStepCurrent(uint64_t step)
{
    stepper.setStepCurrent(step);
}

uint64_t getStepCurrent()
{
    return stepper.getStepCurr();
}

int getMotorDir()
{
    return stepper.getDir();
}

uint64_t getX0(int tramo)
{
    return slider.getX0(tramo);
}


//Mapeo de Slider

void mapeoSlider(Button * inicioLinea, Button * finLinea){
    static int move_to_end = 1;
    static int move_to_start = 0;   
    static int move_adelante = 0;

    static bool show_one_time = true;
    if(show_one_time){
        show_screen("Inicializando", BLANK);
        show_one_time = false;
    }

    //Move to end
    if(move_to_end){
        if(finLinea->getState() == NOT_PRESSED){
            stepper.setDir(ANTIHORARIO);
            stepper.setEnableMotor(ON);
            stepper.setTimeConst(MAX_VEL);
            updateMotor();
        }
        else{
            stepper.setStepCurrent(0);
            delay(500);
            move_to_end = 0;
            move_to_start = 1;
        }        
    }

    //Move to start
    if(move_to_start){
        if(inicioLinea->getState() == NOT_PRESSED){
            stepper.setDir(HORARIO);
            stepper.setEnableMotor(ON);
            stepper.setTimeConst(MAX_VEL);
            updateMotor();
        }
        else{
            slider.maxPasos = (uint64_t)((-1)*(stepper.getStepCurr()));
        //    Serial.println(slider.maxPasos);

            slider.maxPasos -= 200; 
        //    Serial.println(slider.maxPasos);
            delay(500);
            stepper.setStepsRem(100); 
            move_adelante = 1;
            move_to_start = 0;
        }
    }

    //Move forward
    if(move_adelante){
        if(stepper.getStepsRemainig()){
            stepper.setDir(ANTIHORARIO);
            stepper.setEnableMotor(ON);
            stepper.setTimeConst(MAX_VEL);
            updateMotor();
        }
        else{
            move_adelante = 0;
            move_to_end = 1;
            stepper.setStepCurrent(0);
            stepper.setEnableMotor(OFF);
            setState(READY);
            show_one_time = true;
        }
    }    
    


}