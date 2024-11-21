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
Button emergencia = Button(PIN_EMERGENCIA, ACT_LOW);
bool paradaManual = false;
bool iniciando = true;

void readEncoder();
void readButtons(void);
void rutinaEmergencia();



//timers
uint64_t timer_1 = 0;
//uint64_t timer_2 = 0;

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
    InitSlider();
    show_screen("HOLA MUNDO...", BLANK);
    //show_curs(0, 1);
    
    //Set up encoder
    encoder.attachHalfQuad(PIN_ENCODER_A, PIN_ENCODER_B);
	encoder.setCount(0);

    iniciando = true;


}

void loop() {

    //si no hay emergencia
    if(paradaManual == false && iniciando == false){ 
        if(!EG_isEmpty()){
            byte_t event = (byte_t)(EG_getEvent());
        //    Serial.println(event);
            state = fsm(state, event);
            state->actionState();
        }
    }
    else if(iniciando == false){
        //codigo de emergencia
        rutinaEmergencia();   

    }
    
    if(iniciando == true){
        mapeoSlider(&inicioDeLinea, &finDeLinea);
        if(getStateSlider() == READY){
            iniciando = false;
            EG_addExternEvent(NONE);
        }
    }

    //Lectura de encoder y botones
    if(millis() - timer_1 > 100){
        readEncoder();
        readButtons();
        timer_1 = millis();
    }

    switch (getStateSlider()) {
        case START:
        {
            move2origin(&inicioDeLinea);
        }
            break;
        case RUNNING:
        case FINISHED:
        {
            runMotor();
            if (millis() - timer_3 > 200) {
           //     disp_write_number(pasos2cm(getStepCurrent()), PROGRESS_COL, PROGRESS_FIL);
                disp_write_number(getStepCurrent(), PROGRESS_COL, PROGRESS_FIL);
                timer_3 = millis();
            }
        } 
            break;
        case SETTING_MOTOR:
        {
            if (getStepRemaining()) {
                updateMotor();
            }
            if (millis() - timer_3 > 50) {
                //disp_write_number(pasos2cm(getStepCurrent()), DIS_OFFSET, DIS_FIL);
                disp_write_number(getStepCurrent(), DIS_OFFSET, DIS_FIL);
                timer_3 = millis();
            }
        }
        break;
        default:
            break;
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
    
    if(inicioDeLinea.getState() == FLANCO_ACTIVACION){	//Indica inicio de linea apretado
        EG_addExternEvent(INIT_OF_LINE);
	}	
	if(finDeLinea.getState() == FLANCO_ACTIVACION){	//Indica fin de linea apretado
        EG_addExternEvent(END_OF_LINE);
	}
    
    if(emergencia.getState() == FLANCO_ACTIVACION && paradaManual == false && iniciando == false){
        paradaManual = true;
        setState(STOPPED);
        EG_addExternEvent(NONE);
    }

    if(emergencia.getState() == PRESSED && paradaManual == true && iniciando == false){
        //Evento de salida de modo manual.
        EG_addExternEvent(NONE);
        paradaManual = false;
        iniciando = true;
    }
    
}

void rutinaEmergencia(){

    if(!EG_isEmpty()){
        byte_t event = (byte_t)(EG_getEvent());
        switch (event){
        case ENCODER_SWITCH:
            if(getEnableMotor() == OFF){
                setMotorEnable(ON);
                show_screen("Parada|Motor:ON ", "Motor -> encoder");
            }
            else{
                setMotorEnable(OFF);
                show_screen("Parada|Motor:OFF", "Presione encoder");
                setStepRemaining(0);
                setTimeConst(1000);
            }
            break;
        case ENCODER_LEFT:
            if(getEnableMotor() == ON){
                setMotorDir(ANTIHORARIO);
                setMoreSteps(50);
            }
            break;
        case ENCODER_RIGHT:
            if(getEnableMotor() == ON){
                setMotorDir(HORARIO);
                setMoreSteps(50);
            }
            break;
        case INIT_OF_LINE:
            if(getEnableMotor() == ON && getMotorDir() == HORARIO){  
                setStepRemaining(0); 
            }
            break;
        case END_OF_LINE:
            if(getEnableMotor() == ON && getMotorDir() == ANTIHORARIO){
                setStepRemaining(0);
            }
            break;
        case NONE:
            show_screen("Parada|Motor:OFF", BLANK);
            setMotorEnable(OFF);
            setStepRemaining(0);
            setTimeConst(1000);
            break;

        default:
            break;
        }
    }

}

