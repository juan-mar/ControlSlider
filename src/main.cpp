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
#include "SliderCamara.h"

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

    setMotorEnable(ON);
    setStepRemainig(0);


    modifyNumTramos(ADD);
    modifyNumTramos(ADD);


    modifyMovement(1, 1000,2000,5);
    modifyMovement(2, 2000,1000,10);
    modifyMovement(3, 1000,3000,15);   
    setState(RUNNING);

}

void loop() {

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


    if(getStateSlider() == RUNNING){
        runMotor();
        if(getStepCurrent() < getXf(getCurrentTramo())){
            updateMotor();
        }
    }

    
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

