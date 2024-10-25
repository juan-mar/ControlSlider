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



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void show_init();
void show_settings_s1(bool bt);
void show_settings_s2();
void show_parts();

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
bool InitDisp()
{
    display.begin(COL, FIL);
    display.clear();
    show_init();
    display.setCursor(OFFSET_RUN);
    display.print(CURSOR);
}


/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void show_init()
{
    display.clear();
    display.setCursor(ORIGEN);
    display.print(TITLE);
    display.setCursor(0, 1);
    display.print(LINE1);
    display.setCursor(0, 1);
    display.print(CURSOR);
    return;
}


void show_settings_s1(bool bt)
{
    display.clear();
    display.setCursor(ORIGEN);
    if(bt){
        display.print(BT_ON);
    }
    else{
        display.print(BT_OFF);
        display.setCursor(OFFSET_SETMAN);
        display.print(SET_MAN);
    }
    return;
}

void show_settings_s2()
{
    display.clear();
    display.setCursor(ORIGEN);
    display.print(MOVE_MAN);
    return;
}

void show_parts()
{
    display.clear();
    display.setCursor(ORIGEN);
    display.print(PARTS);
    display.setCursor(OFFSET_AD);
    display.print(ADD_DEL);

}