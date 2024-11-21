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
bool paradaEmergencia = false;

//Motor stepper = Motor(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
//Slider slider;
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
    show_screen("Hello World.....", BLANK);
    //show_curs(0, 1);
    
    //Set up encoder
    encoder.attachHalfQuad(PIN_ENCODER_A, PIN_ENCODER_B);
	encoder.setCount(0);

    //modifyNumTramos(ADD);
    //modifyNumTramos(ADD);

    //modifyMovement(1, 0, 1000, 10);
    //modifyMovement(2, 1000, 3000,10);
    //modifyMovement(3, 3000, 5000,15);   
    //setState(RUNNING);
    //Serial.println(getStateSlider());
    //Serial.println(getXf(getCurrentTramo()));

    //setMotorEnable(ON);

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
    
        if(emergencia.getState() == PRESS){
            paradaEmergencia = false;
            EG_addExternEvent(NONE);
            setStepRemaining(0);
        }
    
    
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

