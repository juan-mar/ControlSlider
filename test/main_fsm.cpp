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

//sensores 
ESP32Encoder encoder;
Button encoderSwitch = Button(PIN_ENCODER_SW, ACT_HIGH);
Button inicioDeLinea = Button(PIN_START_LINE, ACT_LOW);
Button finDeLinea = Button(PIN_END_LINE, ACT_LOW);

void readEncoder();
void readButtons(void);

//timers
uint64_t timer_1 = 0;

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

 
}

void loop() {
   
    if(!EG_isEmpty()){
        byte_t event = (byte_t)(EG_getEvent());
        state = fsm(state, event);
        state->actionState();
    }
    
    if(millis() - timer_1 > 100){
        readEncoder();
        readButtons();
        timer_1 = millis();
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
}
