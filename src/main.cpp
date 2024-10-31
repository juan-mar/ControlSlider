#include <Arduino.h>
#include "EventGenerator.h"
#include "fsm.h"

static state_t state;


void setup() {
    EG_init();

    state = FSM_GetInitState();

}

void loop() {
    
    if(!EG_isEmpty()){
        state = fsm(state,(byte_t)(EG_getEvent()));

    }
    state->actionState();



}
