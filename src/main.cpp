#include <Arduino.h>
#include "EventGenerator.h"
#include "fsm.h"
#include "fsmTable.h"
#include "screen.h"
#include "Display.h"

#include "ESP32Encoder.h"

 
void setup() {
    Serial.begin(115200);

    //EG_init();
    //state = FSM_GetInitState();
    //EG_addExternEvent(NONE);
    InitDisp();
    show_screen("Hello World.....", BLANK);
    //show_curs(0, 1);

    //DRV_Enc_Init();
 
}

void loop() {
   
    if(!EG_isEmpty()){
        byte_t event = (byte_t)(EG_getEvent());
        Serial.println(event);
        // state = fsm(state, event);
    }







   // state->actionState();
   
    /*
    long newPosition = encoder.getCount() / 2;

    if(newPosition){
        Serial.println(newPosition);
        char paso_str[16] = "               ";
        paso_str[0] = (int)newPosition + '0';   
        show_screen("Paso Detectado: ", (const char *)paso_str);
    }  
   */
}
