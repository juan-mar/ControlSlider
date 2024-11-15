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

int detectoIni = 0;
int detectoFin = 0;
bool sendAvailable = false;
int paso_n1 = 0;
int paso_n2 = 0;
int paso_n3 = 0;
uint64_t pasos = 0;
uint64_t timer_1 = 0;
uint64_t timer_2 = 0;
void readButtons(void);

void moveStepper(void);

Motor stepper(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
Button encoderSwitch = Button(PIN_ENCODER_SW, ACT_HIGH);
Button inicioDeLinea = Button(PIN_START_LINE, ACT_HIGH);
Button finDeLinea = Button(PIN_END_LINE, ACT_HIGH);

 
void setup() {
    Serial.begin(115200);

//    stepper.calcTraj(0, 1000, 10);
    Serial.println("Hello Wordl");
//    Serial.println(stepper.getTimeConst());
    stepper.setDir(HORARIO);
    Serial.println("HORARIO");
    stepper.setEnableMotor(ON);

    detectoIni = 0;
    detectoFin = 0;
    paso_n1 = 1;
    pasos = 0;
}

void loop() {


    //Primero busco estar en inicio de linea
    //Serial.println(detecto);
    
    //Secuencia para detectar inicio de carrera, esperar 1 segungo
    // y luego moverse en sentido antihorario hasta el fin de linea
    //contando los pasos.
    //Si detecta fin de carrera, se detiene y muestra la cantidad de pasos

    if(detectoIni == 0 && paso_n1 == 1){
        //stepper.sendStep();
        sendAvailable = true;
    }
    else if(detectoIni == 1 && paso_n1 == 1){
        stepper.setEnableMotor(OFF);
        paso_n1 = 0;
        paso_n2 = 1;
        stepper.setDir(ANTIHORARIO);
        Serial.println("AntiHorario");
        sendAvailable = false;  
        delay(1000);
        stepper.setEnableMotor(ON);
    }

    if(detectoFin == 0 && paso_n2 == 1){
        //stepper.sendStep();
        sendAvailable = true;
    }
    else if(detectoFin == 1 && paso_n2 == 1){
        sendAvailable = false;  
        stepper.setEnableMotor(OFF);
        paso_n2 = 0;
        paso_n3 = 1;
        Serial.println("Fin de carrera");
        Serial.println(pasos);
        delay(1000);
        pasos = 0;
        stepper.setDir(HORARIO);
        stepper.setEnableMotor(ON);
        Serial.println("Horario");
        sendAvailable = true;
    }
    
    if(detectoIni == 1 && paso_n3 == 1){
        stepper.setEnableMotor(OFF);
        paso_n3 = 0;
        sendAvailable = false;
        Serial.println("Fin de carrera");
        Serial.println(pasos);  
        delay(1000);
    }
  
    
    if(millis() - timer_1 > 100){
        if(inicioDeLinea.getState() == PRESS){	//Indica inicio de linea apretado
            detectoIni = 1; //Apretado
        }
        else{
            detectoIni = 0; //NO apretado
        }     
        if(finDeLinea.getState() == PRESS){	//Indica fin de linea apretado
            detectoFin = 1;
        }
        else{
            detectoFin = 0;
        }   
    }


    if(sendAvailable){
        if(micros() - timer_2 >1000){
            stepper.sendStep();
            if(paso_n2 == 1){
                Serial.println(pasos);
                pasos++;
            }
            if(paso_n3 == 1){
                pasos++;
                Serial.println(pasos);
            }
            timer_2 = micros();
        }   
    }
}



