#include <Arduino.h>
#include "CircularBuffer.h"
#include "fsm.h"
#include "fsmTable.h"
#include "screen.h"
#include "Display.h"
#include "board.h"
#include "Button.h"
#include "EventGenerator.h"
#include "ESP32Encoder.h"
#include "Stepper.h"
#include "slider.h"

//sensores 
ESP32Encoder encoder;
Button encoderSwitch = Button(PIN_ENCODER_SW, ACT_LOW);
Button inicioDeLinea = Button(PIN_START_LINE, ACT_HIGH);
Button finDeLinea = Button(PIN_END_LINE, ACT_HIGH);
Button emergencia = Button(PIN_EMERGENCIA, ACT_HIGH);
bool paradaEmergencia = false;

Motor stepper = Motor(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
Slider slider;
void readEncoder();
void readButtons(void);
void rutinaEmergencia();
void rutinaRun();


//timers
uint64_t timer_1 = 0;
uint64_t timer_2 = 0;

uint64_t timer_3 = 0;

//Cola de enventos
#define MAX_EVENT   100

//State machine
state_t state;

void setup() {
    Serial.begin(115200);
    
    EG_init();
    state = FSM_GetInitState();
    EG_addExternEvent(NONE);
    InitDisp();
    show_screen("Hello World.....", BLANK);
    //show_curs(0, 1);
    
    //Set up encoder
    encoder.attachHalfQuad(PIN_ENCODER_A, PIN_ENCODER_B);
	encoder.setCount(0);
    stepper.setEnableMotor(ON);
    stepper.setSteps(0);

    slider.modificarTramo(0,1000,10000,20);

 
}

void loop() {
/*
    //si no hay emergencia
    if(paradaEmergencia == false){ 
        if(!EG_isEmpty()){
            byte_t event = (byte_t)(EG_getEvent());
            Serial.println(event);
            state = fsm(state, event);
            state->actionState();
        }
    }
    else{
        //codigo de emergencia
        rutinaEmergencia();       
    }

*/
   
    //Lectura de encoder y botones
    if(millis() - timer_1 > 100){
        readEncoder();
        readButtons();
        timer_1 = millis();
    }

    if(millis() - timer_3 > 50){
        disp_write_number(stepper.getStepCurr(),0,1);
        Serial.println(stepper.getStepCurr());
        timer_3 = millis();
    }

    
    //Mover motor
    rutinaRun();



    
}


void readEncoder(void){
    int64_t count = encoder.getCount();
    if(count > 0){
        EG_addExternEvent(ENCODER_RIGHT);
        encoder.setCount(0);
    }
    else if(count < 0){
        EG_addExternEvent(ENCODER_LEFT);    
        encoder.setCount(0);
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
    if(emergencia.getState() == PRESS && paradaEmergencia == false){
        paradaEmergencia = true;
        EG_addExternEvent(NONE);
    }

    static uint64_t restartProgram = 0;
    if(emergencia.getState() == PRESS && paradaEmergencia == true){
        restartProgram++;
        if(restartProgram == 10*5){
            EG_addExternEvent(NONE);
            paradaEmergencia = false;
            restartProgram = 0;
            show_screen("Reiniciando...  ","Soltar boton    ");
            delay(3000);
        }
    }
    
}

void rutinaEmergencia(){
    /*
        if(emergencia.getState() == PRESS){
            paradaEmergencia = false;
            EG_addExternEvent(NONE);
            stepper.setSteps(0);

        }
    */
    
    if(!EG_isEmpty()){
        byte_t event = (byte_t)(EG_getEvent());
        switch (event){
        case ENCODER_SWITCH:
            if(stepper.getEnableMotor() == OFF){
                stepper.setEnableMotor(ON);
                show_screen("Parada|Motor:ON ", "Motor -> encoder");
            }
            else{
                stepper.setEnableMotor(OFF);
                show_screen("Parada|Motor:OFF", "Presione encoder");
                stepper.setSteps(0);
                stepper.setTimeConst(1000);
            }
            break;
        case ENCODER_LEFT:
            if(stepper.getEnableMotor() == ON){
                stepper.setDir(ANTIHORARIO);
                stepper.setMoreSteps(50);
            }
            break;
        case ENCODER_RIGHT:
            if(stepper.getEnableMotor() == ON){
                stepper.setDir(HORARIO);
                stepper.setMoreSteps(50);
            }
            break;
        case INIT_OF_LINE:
            if(stepper.getEnableMotor() == ON && stepper.getDir() == HORARIO){  
                stepper.setSteps(0);
            }
            break;
        case END_OF_LINE:
            if(stepper.getEnableMotor() == ON && stepper.getDir() == ANTIHORARIO){
                stepper.setSteps(0);
            }
            break;
        case NONE:
            show_screen("Parada|Motor:OFF", BLANK);
            stepper.setEnableMotor(OFF);
            stepper.setSteps(0);
            stepper.setTimeConst(1000);
            break;

        default:
            break;
        }
    }
}



void rutinaRun(){
    static int tramos_faltantes = slider.numTramos;
    static int go_origin = 1;
    static int go_X0 = 0;
    static int currentTramo = 0;
    static int cantTramos = slider.numTramos;
    static int newTramo = 1;

    if(go_origin){
        show_screen("Yendo a inicio", "Moviendo motor");
        stepper.setDir(HORARIO);
        stepper.setEnableMotor(ON);
        while(inicioDeLinea.getState() == NOT_PRESSED){
            if(micros() - timer_2 > (1000/2)){
                stepper.sendStep();
                timer_2 = micros();
            }
        }
        delay(500);
        stepper.setStepCurrent(0);
        //stepper.setEnableMotor(ON);
        stepper.setDir(ANTIHORARIO);
        uint64_t x0_ = slider.getX0(0);
        show_screen("Yendo a x0", "Moviendo motor");

        //Go to Initial Position
        while(stepper.getStepCurr() < x0_){
            if(micros() - timer_2 > (1000/2)){
                stepper.sendStep();
                timer_2 = micros();
            }
        }
        delay(500);
        go_origin = 0;
    }
    
    stepper.setDir(ANTIHORARIO);

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