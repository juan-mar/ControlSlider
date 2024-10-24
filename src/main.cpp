#include <Arduino.h>
#include "EventGenerator.h"
#include "Button.h"
#include <stdio.h>


#define PIN_BOTON_1 2

Button boton1 = Button(PIN_BOTON_1, ACT_HIGH);

uint64_t timers_ = 0;

uint64_t contBoton = 0;




void setup(){
	Serial.begin(9600);
	EG_init();

	
}

void loop() {
	Serial.println("Hola Mundo");
	delay(1*1000);

	if(!EG_isEmpty()){
		while (EG_numberOfElements()){
			Serial.printf("Ocurrio evento: ",(uint8_t)(EG_getEvent()));
			Serial.print("\n");
		}
		
		
	}






}


