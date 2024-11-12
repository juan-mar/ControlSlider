#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

/*******************************************************************************
 * CONEXION DE FINALES DE CARRERA
 ******************************************************************************/
#define PIN_START_LINE      4
#define PIN_END_LINE        5

/*******************************************************************************
 * CONEXION DE BOTON
 ******************************************************************************/
#define PIN_EMERGENCIA      36


/*******************************************************************************
 * CONEXION DE MOTORES
 ******************************************************************************/
#define PIN_MOTOR_DIR       21
#define PIN_MOTOR_STEP      19
#define PIN_MOTOR_EN        18

/*******************************************************************************
 * CONEXION DE SENSORES
 ******************************************************************************/
#define PIN_ENCODER_A         35
#define PIN_ENCODER_B         34
#define PIN_ENCODER_SW        39

/*******************************************************************************
 * CONEXION DE DISPLAY
 ******************************************************************************/
#define PIN_LCD_RS 32
#define PIN_LCD_EN 33
#define PIN_LCD_D4 25
#define PIN_LCD_D5 26
#define PIN_LCD_D6 27
#define PIN_LCD_D7 14


/*
Componentes
tira de pines macho x4 (motor)
tira de pines macho x14 (botones y test)
tira de pines macho x6 (jumpers)
tira de pines macho x24 (total)
jumpers x3

tira de piens hembra x15 x2 (ESP32)
tira de pines hembra x12 (display)
tira de pines hembra x8 x2 (DVR8825)
tira de pines hembra x58 (total)

bornera doble x2

preset 10k x1

tension mayor a 16V
cap 100n x4
cap 10uF x2
cap 1uF x1

res 10k x3
res 220 x1

7805 x1



*/




#endif /* BOARD_BOARD_H_ */



