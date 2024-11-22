#include <Arduino.h>
#include "Stepper.h"
#include "SliderCamara.h"
#include "board.h"
uint64_t timer_1 = 0;
uint64_t timer_2 = 0;


void moveStepper(void);

Motor stepper = Motor(PIN_MOTOR_STEP, PIN_MOTOR_DIR, PIN_MOTOR_EN);
 
void setup() {
    Serial.begin(115200);
   
    stepper.setEnableMotor(ON);    
}

void loop() {

    while(stepper.getStepsRemainig()){
        if(millis() - timer_1 > (stepper.getTimeConst()/2)){
            moveStepper();
            timer_1 = millis();
        }
    }
    delay(2000);
    
    stepper.setDir(!stepper.getDir());
    Serial.println("Direccion");
    Serial.println(stepper.getDir());


}

