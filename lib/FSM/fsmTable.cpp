/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsmTable.h"

enum eventos{
	RUN = 100,
	SETTING,
	MANUAL,
	EMERGENCY,
	PARTS

};

enum posiciones{
	LEFT_UP,
	LEFT_DOWN,
	RIGH_UP,
	RIGH_DOWN
};

/*******************************************************************************
 * Foward declarations States
 ******************************************************************************/
extern state_edge_t estado_init[];
extern state_edge_t enter[];

extern state_edge_t menu[];
extern state_edge_t settings[];
extern state_edge_t running[];

extern state_edge_t bluetoothMode[];
extern state_edge_t manualMode[];
extern state_edge_t emergencyMode[];

extern state_edge_t parts[];

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void do_nothing(void);
static void incrementCursorX(void);
static void incrementCursorY(void);
static void decrementCursorX(void);
static void decrementCursorY(void);

static void menuAction();
static void enterAction();
static void enterMenu();
static void enterSetting();
static void enterAction();
static void enterAction();




/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
state_edge_t estado_init[] = {
	{NONE, menu, do_nothing, do_nothing}
};

state_edge_t menu[] = {
	{RIGH, menu, incrementCursorX, menuAction},
	{LEFT, menu, decrementCursorX, menuAction},
	{UP, menu, incrementCursorY, menuAction},
	{DOWN, menu, decrementCursorX, menuAction},	
	{ENTER, enter, enterMenu, enterAction},
	{INIT_OF_LINE, menu, do_nothing, menuAction},
	{END_OF_LINE, menu, do_nothing, menuAction},	
	{NONE, menu, do_nothing, do_nothing}
};

state_edge_t enter[] = {
	{NONE, estado_init, do_nothing,do_nothing},
	{RUN, running, do_nothing,do_nothing},
	{SETTING, settings, do_nothing,do_nothing},
	{NONE, estado_init, do_nothing,do_nothing}

};

state_edge_t settings[] = {
	{NONE, estado_init, do_nothing,do_nothing}

};

state_edge_t running[] = {
	{NONE, estado_init, do_nothing,do_nothing}

};


state_edge_t bluetoothMode[] = {
	{NONE, estado_init, do_nothing,do_nothing}

};

state_edge_t manualMode[] = {
	{NONE, estado_init, do_nothing,do_nothing}

};

state_edge_t emergencyMode[] = {
	{NONE, estado_init, do_nothing,do_nothing}

};


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t cursorX = 0;
static uint8_t cursorY = 0;
static uint8_t cursorXY = 0;	//0b 0000 00xy

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

state_t FSM_GetInitState(void) {
 	return estado_init;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void do_nothing(){}

/*******************************************************************************
 * 						MENU FUNCTIONS
 ******************************************************************************/
static void menuAction(void){
	
}

static void incrementCursorX(){
	cursorX++;
	cursorX &= 0b1;
	cursorXY = (cursorX<<1)|(cursorY);
}

static void incrementCursorY(){
	cursorY++;
	cursorY &= 0b1;
	cursorXY = (cursorX<<1)|(cursorY);
}

static void decrementCursorX(){
	cursorX--;
	cursorX &= 0b1;
	cursorXY = (cursorX<<1)|(cursorY);
}

static void decrementCursorY(){
	cursorY--;
	cursorY &= 0b1;
	cursorXY = (cursorX<<1)|(cursorY);
}

/*******************************************************************************
 * 						ENTER FUNCTIONS
 ******************************************************************************/
static void enterAction(){

}
static void enterMenu(){
	uint8_t xy = (cursorX<<1)|(cursorY);
	switch (xy)
	{
	case LEFT_UP:
	case LEFT_DOWN:
		EG_setEvent((events_t)RUN);
		break;
	case RIGH_UP:
	case RIGH_DOWN:
		EG_setEvent((events_t)SETTING);
		break;
	default:
		break;
	}
}
static void enterSetting(){

}
static void enterParts(){

}

