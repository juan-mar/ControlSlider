#include <Arduino.h>
#include "EventGenerator.h"
#include "fsm.h"
#include "fsmTable.h"
#include "screen.h"
#include "Display.h"
#include "Stepper.h"

#include "ESP32Encoder.h"

uint64_t timer_1 = 0;

void moveStepper(void);

Motor stepper(STEP, DIR, EN);
 
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
    stepper.calcTraj(0, 100, 10);
    if(millis() - timer_1 > (stepper.getTimeConst()/2)){
        moveStepper();
        timer_1 = millis();
    }


}


void moveStepper()
{
    stepper.toggleMove();
}