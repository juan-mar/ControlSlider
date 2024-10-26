/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "Display.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

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
    show_screen(TITLE, LINE1);
    display.setCursor(COL0, FILA1);
    display.print(CURSOR);
    selector.fila = FILA1;
    selector.columna = COL0;
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

void show_screen(char * fila1, char * fila2)
{
    display.clear();
    display.setCursor(COL0, FILA0);
    display.print(fila1);
    display.setCursor(COL0, FILA1);
    display.print(fila2);
    return;
}

/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



