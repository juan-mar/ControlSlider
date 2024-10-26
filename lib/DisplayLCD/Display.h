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
#define COL0        0
#define FILA0       0
#define FILA1       1



//PANTALLA DE INICIO
#define TITLE       "Camera Slider   "
#define LINE1       " Run   Settings "           
#define LINE2       " Continue    End"

#define OFFSET_SETTINGS     7
#define OFFSET_END          12 

//SETTINGS
#define BT_ON       " Bluetooth   ON "
#define BT_OFF      " Bluetooth   OFF"
#define SET_MAN     " Set Manually   "
#define MOVE_MAN    " Move Manually  "


//PARTS
#define PARTS       " Part           "
#define ADD_DEL     " Add         Del"

#define OFFSET_DEL  12

//PART SETTINGS
#define POSITIONS   " Xo:    Xf:    B"
#define TIME_VEL    " T:   s V:   m/s"

#define OFFSET_XF   7
#define OFFSET_B    15
#define OFFSET_VEL  7

//RUNNING
#define RUN         "Running...      "
#define PAUSE       " Pause          "

#define OFFSET_PER  12  //para poner el porcentaje si se desea

       
/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
//Funcion de inicializacion del display. Muestra pantalla de inicio con el cursor en Run
void InitDisp();

//Funcion que muestra una pantalla predeterminada
void show_screen(char * fila1, char * fila2);

//Funcion que posiciona el cursor en determinada ubicacion. Primero lo borra de la ubicacion anterior
void show_curs(int col, int fil);



#endif /* DISPLAY_H_ */