/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "EventGenerator.h"
#include "Arduino.h"
#include "CircularBuffer.hpp"
#include "Button.h"
#include "board.h"
#include <stdint.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_EVENT   100

#define CLK   APB_CLK_FREQ 	// Hz
#define FREQ  (1000000)  		// Hz  
#define TIME_EVENT_INTERRUPT  (0.100f) //s
#define TICK_S (1.0f/(float)FREQ)
#define TIME_2_TICKS(x) ((uint64_t)((x)/TICK_S))

#define LONG_PUSH_TIME	(3.0) //s
#define LONG_PUSH_TICK	((uint32_t)(LONG_PUSH_TIME/TIME_EVENT_INTERRUPT))

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void new_mov_event(void);
static void new_enter_event(void);
static void IRAM_ATTR Timer0_ISR(void);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static CircularBuffer <uint8_t, MAX_EVENT> eventBuffer;
static Button botonDerecha = Button(PIN_RIGHT_BUTTON, ACT_HIGH);
static Button botonIzquierda = Button(PIN_LEFT_BUTTON, ACT_HIGH);
static Button botonEnter = Button(PIN_ENTER_BUTTON, ACT_HIGH);
static Button inicioDeLinea = Button(PIN_START_LINE, ACT_LOW);
static Button finDeLinea = Button(PIN_END_LINE, ACT_LOW);
static Button * listButton[5] = {&botonDerecha,&botonIzquierda,&botonEnter,
									&inicioDeLinea,&finDeLinea};
static uint32_t countButtonTicks[5] = {0};
static hw_timer_t *Timer0_Cfg = NULL;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void EG_init(void){
	Timer0_Cfg = timerBegin(0, CLK/FREQ, true); //TIMER_0, PRESCALES=80, COUNT_UP=TRUE
  	timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true); //TIMER_0, CALL_BACK, MODE_EDGE=TRUE
  	timerAlarmWrite(Timer0_Cfg, TIME_2_TICKS(TIME_EVENT_INTERRUPT), true); //TIMER_0, N_TICKS, RELOAD=TRUE
	timerAlarmEnable(Timer0_Cfg); //ENABLE


}


events_t EG_getEvent(void){
	return (events_t)eventBuffer.pop();
}

void EG_addExternEvent(events_t event){
	eventBuffer.push(event);
}

bool EG_isEmpty(void){
	return eventBuffer.isEmpty();
}

uint8_t EG_numberOfElements(void){
	return eventBuffer.size();
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void new_mov_event(void){
/*	row_index++;
	row_index &= 0b11;
	colaPush(&event_queue, MOV_ARRIBA);
*/


}

static void new_enter_event(void){
	
}

static void IRAM_ATTR Timer0_ISR(){
	for (uint8_t i = 0; i < 5; i++){
		state_t estado = listButton[i]->getState();
		if(estado == PRESS){
			countButtonTicks[i]++;
		}
		else if(estado == PRESSED){
			if(countButtonTicks[i] > LONG_PUSH_TICK){
				eventBuffer.push(i+10);
			}
			eventBuffer.push(i);
			countButtonTicks[i] = 0;
		}
	}	
}
