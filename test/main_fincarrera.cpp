#include <Arduino.h>
#include "EventGenerator.h"
#include "fsm.h"
#include "fsmTable.h"
#include "screen.h"
#include "Display.h"
#include "Stepper.h"
#include "board.h"
#include "Button.h" 
#include "ESP32Encoder.h"

int detecto = 0;
uint64_t pasos = 0;
uint64_t timer_1 = 0;
uint64_t timer_2 = 0;
void readButtons(void);

void moveStepper(void);

Motor stepper(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
Button encoderSwitch = Button(PIN_ENCODER_SW, ACT_HIGH);
Button inicioDeLinea = Button(PIN_START_LINE, ACT_LOW);
Button finDeLinea = Button(PIN_END_LINE, ACT_LOW);

 
void setup() {
    Serial.begin(115200);

//    stepper.calcTraj(0, 1000, 10);
    Serial.println("Hello Wordl");
//    Serial.println(stepper.getTimeConst());
    stepper.setDir(HORARIO);
    
}

void loop() {
    if(detecto){	//Indica inicio de linea apretado
        Serial.println("Inicio de linea - 2");

	}
    else{
        if(millis() - timer_2 > (10/2)){
            moveStepper();
            timer_2 = millis();
        }
    }
	
    //stepper.setDir();

    if(millis() - timer_1 > 100){
        if(inicioDeLinea.getState() == PRESS){	//Indica inicio de linea apretado
            detecto = 1;
            Serial.println("Inicio de linea");
            Serial.println(pasos/2);
	    }
        
    }



}


void moveStepper()
{
    if(!detecto){
        stepper.sendStep();
        pasos++;

    }
}


void readButtons(void){
	if(encoderSwitch.getState() == PRESSED){
        EG_addExternEvent(ENCODER_SWITCH);
	}
	if(inicioDeLinea.getState() == PRESS){	//Indica inicio de linea apretado
        EG_addExternEvent(INIT_OF_LINE);
	}	
	if(finDeLinea.getState() == PRESS){	//Indica fin de linea apretado
        EG_addExternEvent(END_OF_LINE);
	}
}