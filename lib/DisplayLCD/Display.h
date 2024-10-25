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

#define CURSOR  ">"
#define ORIGEN  0,0
#define FILA1   0,1

//PANTALLA DE INICIO
#define TITLE       "Camera Slider   "
#define LINE1       " Run   Settings "           
#define LINE2       " Continue    End"
#define OFFSET_RUN      FILA1                 //Primero columna y despues fila
#define OFFSET_SETTINGS 7,1
#define OFFSET_CONTINUE FILA1
#define OFFSET_END      12,1     

//SETTINGS
#define BT_ON       " Bluetooth   ON "
#define BT_OFF      " Bluetooth   OFF"
#define SET_MAN     " Set Manually   "
#define MOVE_MAN    " Move Manually  "

#define OFFSET_BT       ORIGEN
#define OFFSET_ONOFF    12,1
#define OFFSET_SETMAN   FILA1

//PARTS
#define PARTS       " Part           "
#define ADD_DEL     " Add         Del"

#define OFFSET_AD   FILA1

//PART SETTINGS
#define POSITIONS   " Xo:    Xf:    B"
#define TIME_VEL    " T:   s V:   m/s"

//RUNNING
#define RUN         "Running...      "

       
/*******************************************************************************
 * DEFINICION DE FUNCIONES
 ******************************************************************************/
bool InitDisp();



#endif /* DISPLAY_H_ */