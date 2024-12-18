/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "Button.h"
#include "Arduino.h"

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

Button::Button(int pin, activeLogic_t activeLogic){ 
    this->pin = pin;
    this->activeLogic = activeLogic;
    prevState = NOT_PRESSED;
    pinMode(this->pin, INPUT);

}

Button::~Button(){

}

stateButtton_t Button::getState(){
    stateButtton_t state = (digitalRead(this->pin) == activeLogic) ? PRESS : NOT_PRESSED;
    
    if(state == NOT_PRESSED && prevState == PRESS){
        this->prevState = NOT_PRESSED;
        return FLANCO_DESACTIVACION;
    }
    else if(state == PRESS){
        this->prevState = PRESS;
        return PRESS;
    }
    else if(state == PRESS && prevState == NOT_PRESSED){
        this->prevState = PRESS;
        return FLANCO_ACTIVACION;
    }
    else{
        this->prevState = NOT_PRESSED;
        return NOT_PRESSED;
    }

    return NOT_PRESSED;


/*
    if(state == NOT_PRESSED && prevState == PRESS){
        this->prevState = NOT_PRESSED;
        return FLANCO_DESACTIVACION;
    }
    else if(state == PRESS && prevState == NOT_PRESSED){
        this->prevState = FLANCO_ACTIVACION;
        return FLANCO_ACTIVACION;
    }
    
    return state;
*/

}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


