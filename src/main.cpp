#include <Arduino.h>
#include "EventGenerator.h"
#include "fsm.h"
#include "fsmTable.h"
#include "screen.h"
#include "Display.h"

#include "ESP32Encoder.h"
#include "Encoder.h"

static state_t state;
ESP32Encoder encoder;

#define CLK 22 // CLK ENCODER 
#define DT 23// DT ENCODER 
 
void setup() {
    Serial.begin(115200);

    //EG_init();
    //state = FSM_GetInitState();
    //EG_addExternEvent(NONE);
    InitDisp();
    show_screen("Hello World.....", BLANK);
    //show_curs(0, 1);

 //   DRV_Enc_Init();
  encoder.attachHalfQuad ( DT, CLK );
  encoder.setCount ( 0 );

}

void loop() {
    /*
    if(!EG_isEmpty()){
        byte_t event = (byte_t)(EG_getEvent());
        Serial.println(event);
       // state = fsm(state, event);

    }
    state->actionState();
    */
    bool encoder_on = is_encoderRotating();
      long newPosition = encoder.getCount() / 2;

    if(newPosition){
        int paso = get_vueltas();
        Serial.println(newPosition);
        char paso_str[16] = "               ";
        paso_str[0] = paso + '0';   
        show_screen("Paso Detectado: ", (const char *)paso_str);
    }  
    int boton = get_boton(); 
    if(boton){
        Serial.println("Dentro del if");
        char boton_str[16] = "               ";
        boton_str[0] = boton + '0';   
        show_screen("Boton Detectado: ", (const char *)boton_str);
    } 
    //Serial.println("Hello World");
    //delay(2000);
}
