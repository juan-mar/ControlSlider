#include <Arduino.h>
#include "Encoder.h"



void setup() {
    Serial.begin(9600);
    DRV_Enc_Init();


}

void loop() {
    
    int paso = get_paso();
    if(paso > 0){
        Serial.print("Derecha: ");
        Serial.println(paso);

    }
    else if(paso < 0){
        Serial.print("Izquierda: ");
        Serial.println((-1)*paso);
    }
    else{

    }

    int boton = get_boton();
    if(boton){
        Serial.print("Boton apretado");
        Serial.println(boton);
    }
    delay(1000);
}