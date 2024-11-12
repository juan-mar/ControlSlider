#include <Arduino.h>
#include "Stepper.h"
#include "board.h"
#define CLK   APB_CLK_FREQ 	// Hz
#define FREQ  (10000000)  		// Hz  
#define TIME_EVENT_INTERRUPT  (0.000002f) //s
#define TICK_S (1.0f/(float)FREQ)
#define TIME_2_TICKS(x) ((uint64_t)((x)/TICK_S))

uint64_t timer_1 = 0;
hw_timer_t *Timer0_Cfg = NULL;

void moveStepper(void);

Motor stepper = Motor(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
 
void setup() {
    Serial.begin(115200);
    Serial.println("Hello Wordl");    

    Timer0_Cfg = timerBegin(0, CLK/FREQ, true); //TIMER_0, PRESCALES=80, COUNT_UP=TRUE
  	timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true); //TIMER_0, CALL_BACK, MODE_EDGE=TRUE
  	
    timerAlarmWrite(Timer0_Cfg, TIME_2_TICKS(TIME_EVENT_INTERRUPT), true); //TIMER_0, N_TICKS, RELOAD=TRUE
	timerAlarmEnable(Timer0_Cfg); //ENABLE


    stepper.calcTraj(0, 1000, 5);
    Serial.println("Hello Wordl");
    Serial.println(stepper.getTimeConst());
    
}

void loop() {

    while(stepper.getStepsRemainig()){
        if(millis() - timer_1 > (stepper.getTimeConst()/2)){
            moveStepper();
            timer_1 = millis();
        }
    }
    delay(2000);
    
    stepper.calcTraj(0, 1000, 5);
    stepper.setDir(!stepper.getDir());
    Serial.println("Direccion");
    Serial.println(stepper.getDir());

    delay(3000);
   // stepper.setDir(!stepper.getDir());

}

void Timer0_ISR(void){
    stepper.sendStep();
}   

void moveStepper()
{
    stepper.sendStep();
}