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
int paso_n1 = 0;
int paso_n2 = 0;
uint64_t pasos = 0;
uint64_t timer_1 = 0;
uint64_t timer_2 = 0;
void readButtons(void);

void moveStepper(void);

Motor stepper(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
Button encoderSwitch = Button(PIN_ENCODER_SW, ACT_HIGH);
Button inicioDeLinea = Button(PIN_START_LINE, ACT_HIGH);
Button finDeLinea = Button(PIN_END_LINE, ACT_LOW);

 
void setup() {
    Serial.begin(115200);

//    stepper.calcTraj(0, 1000, 10);
    Serial.println("Hello Wordl");
//    Serial.println(stepper.getTimeConst());
    stepper.setDir(HORARIO);
    detecto = 0;
}

void loop() {

    //Primero busco estar en inicio de linea
    if (paso_n1 == 1 && detecto == 0){
        stepper.setDir(HORARIO);
        stepper.enableMotor(ON);
        paso_n2 = 0;
    }
    else{
        /* code */
    }
    



    if(inicioDeLinea.getState() == PRESS){
        //estoy en inicio de linea
        detecto = 1;
        delay(1000); //freno
        stepper.setDir(ANTIHORARIO);
    }
    else{
        detecto = 0;

    }



    Serial.println(digitalRead(PIN_START_LINE));
    if(detecto){	//Indica inicio de linea apretado
     //   Serial.println("Inicio de linea - 2");
       //     Serial.println(detecto);

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
        }
        else{
            detecto = 0;
        }        
    }



}


void moveStepper()
{
    if(paso_n1 == 1 && detecto == 0){
        stepper.sendStep();
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