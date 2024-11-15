/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "Display.h"
#include "board.h"
#include <string>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define FILA_0 0
#define FILA_1 1
#define COL_0 0
#define COL_1 1


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
#define EN      PIN_LCD_EN
#define RS      PIN_LCD_RS
#define D4      PIN_LCD_D4
#define D5      PIN_LCD_D5
#define D6      PIN_LCD_D6
#define D7      PIN_LCD_D7

typedef struct{
    int fila;
    int columna;
}curs_t;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
curs_t selector;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static LiquidCrystal display(RS, EN, D4, D5, D6, D7);   //checkear el static

/*******************************************************************************
 *******************************************************************************
    GLOBAL METHODS DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void InitDisp()
{
    display.begin(COL, FIL);
    display.clear();
    show_screen(BLANK, BLANK);
    display.setCursor(COL_0, FILA_0);
    display.print(CURSOR);
    selector.fila = 0;
    selector.columna = 0;
    return;
}

void show_curs(int col, int fil)
{
    display.setCursor(selector.columna, selector.fila);
    display.print(" ");             //borra el selector de la posicion anterior
    display.setCursor(col, fil);
    display.print(CURSOR);          //muestro el cursor en la nueva posicion
    selector.columna = col;         //cambio las posiciones del cursor
    selector.fila = fil;
    return;
}

void show_screen(const char * fila1, const char * fila2)
{
    display.clear();
    display.setCursor(COL_0, FILA_0);
    display.print(fila1);
    display.setCursor(COL_0, FILA_1);
    display.print(fila2);
    return;
}

void disp_write(const char * word, int pos_x, int pos_y)
{
    display.setCursor(pos_x, pos_y);
    display.print(word);
}

void disp_write_number(int number, int pos_x, int pos_y)
{
    display.setCursor(pos_x, pos_y);
    display.print(number, 10); //base decimal
}
/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



