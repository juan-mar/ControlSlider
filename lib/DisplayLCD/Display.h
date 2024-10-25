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

//PANTALLA DE INICIO
#define TITLE       "Camera Slider   "
#define LINE1       " Run   Settings "

//SETTINGS
#define BT_ON       " Bluetooth    ON"
#define BT_OFF      " Bluetooth   OFF"
#define SET_MAN     " Set Manually   "

//PARTS
#define PARTS       " Part           "

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