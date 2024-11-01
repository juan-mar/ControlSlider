#ifndef DISPLAY_H_
#define DISPLAY_H_

#include<Arduino.h>
#include <LiquidCrystal.h>



/*******************************************************************************
 * CONEXION DE PINES
 ******************************************************************************/
#define EN      33
#define RS      32
#define D4      27
#define D5      14
#define D6      25
#define D7      13

/*******************************************************************************
 * DEFINICION DE CONSTANTES
 ******************************************************************************/
#define FIL     2
#define COL     16

//definiciones generales
#define CURSOR      ">"
#define BLANK       "                "
       
/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
//Funcion de inicializacion del display. Muestra pantalla de inicio con el cursor en Run
void InitDisp();

//Funcion que muestra una pantalla predeterminada
void show_screen(const char * fila1, const char * fila2);

//Funcion que posiciona el cursor en determinada ubicacion. Primero lo borra de la ubicacion anterior
void show_curs(int col, int fil);



#endif /* DISPLAY_H_ */