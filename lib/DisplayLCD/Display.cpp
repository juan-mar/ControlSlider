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
enum estados{
    INIT_SC,
    SETTINGS1_SC,
    SETTINGS2_SC,
    PARTS_SC,
    PARTS_SETTINGS_SC,
    RUNNING_SC,
    PAUSED_SC
};

typedef struct{
    int fila;
    int columna;
}curs_t;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
int state;

curs_t selector;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void show_screen(char * fila1, char * fila2);
void show_curs(int col, int fil);


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
    display.setCursor(FILA1);
    display.print(CURSOR);
    state = INIT_SC;
    selector.fila = 1;
    selector.columna = 0;
    return;
}

void SetCur(bool x, bool y) //x: izq o der; y:arriba o abajo
{
    switch(state)
    {
        case INIT_SC: //sabemos que aca el curosr solo puede estar en la fila 1
        {
            if ((selector.columna == 0) && (x == DER))
                show_curs(OFFSET_SETTINGS, 1);
            else if ((selector.columna == OFFSET_SETTINGS) && (x == IZQ))
                show_curs(OFFSET_RUN_CONT, 1);
            break;
        }
        case SETTINGS1_SC:
        {
            if((selector.fila == 0) && (y == ABAJO))
                show_curs(FILA1);
            else if((selector.fila == 1) && (y == ARRIBA))
                show_curs(ORIGEN);
            else if((selector.fila == 1) && (y == ABAJO)) //en este caso tengo que cambiar de pantalla!
            {
                state = SETTINGS2_SC;
                show_screen(MOVE_MAN, BLANK);
                show_curs(ORIGEN);
            }
            break;
        }
        case SETTINGS2_SC:
        {
            if((selector.fila == 0) && (y == ARRIBA)) //en este caso tengo que cambiar de pantalla!
            {
                state = SETTINGS1_SC;
                show_screen(BT_OFF, SET_MAN); //checkear tema bluetooth!!
                show_curs(FILA1);
            }
            break;
        }
        case PARTS_SC:
        {
            break;
        }
        case PARTS_SETTINGS_SC:
        {
            break;
        }
        case RUNNING_SC:
        {
            break;
        }

    }

}


/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void show_screen(char * fila1, char * fila2)
{
    display.clear();
    display.setCursor(ORIGEN);
    display.print(fila1);
    display.setCursor(FILA1);
    display.print(fila2);
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
