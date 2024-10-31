/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsmTable.h"



/*******************************************************************************
 * Foward declarations States
 ******************************************************************************/
extern state_edge_t estado_init[];

extern state_edge_t menu[];
extern state_edge_t settings[];
extern state_edge_t run[];

extern state_edge_t bluetooth[];
extern state_edge_t set_manually[];

extern state_edge_t edit_parts[];

extern state_edge_t selec_x0[];
extern state_edge_t selec_xf[];
extern state_edge_t selec_delta_t[];
extern state_edge_t selec_vel[];

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
enum eventos{
	RUN = 100,
	SETTING,
	BLUETOOTH,
	MANUAL,
	EDIT_PARTS,
	ADD_PART,
	DELETE_PART,
	SELEC_X0,
	SELEC_XF,
	SELEC_DELTA_T,
	SELEC_VEL,
	BACK
};

enum posiciones{
	LEFT_UP,
	LEFT_DOWN,
	RIGH_UP,
	RIGH_DOWN
};

#define MAX_ITEMS 10

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct{
	uint8_t item_numer;
	uint8_t item_event_select;
	char* name;
	uint8_t len_name;
}item_t;

typedef struct{
	item_t item[MAX_ITEMS];
	uint8_t item_selec;
	uint8_t item_cant;
}menu_items_t;



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void do_nothing(void);

static void show_menu(void);
static void show_run(void);
static void show_settings(void);
static void show_bluetooth(void);
static void show_set_manually(void);
static void show_part_n(void);
static void show_add_part(void);
static void show_delete_part(void);

//Items selector
static void nextItem(void);
static void prevItem(void);
static void selectItem(void);

//Settings FUNCTIONS
static void activeBluetooth(void);


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
/*Estados:
	Menu principal
	Settings
	Run
	Bluetooth
	Set manually



*/

state_edge_t estado_init[] = {
    {NONE, menu, do_nothing, do_nothing}
};

state_edge_t menu[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, menu, nextItem, show_menu},
    {ENCODER_LEFT, menu, prevItem, show_menu},
	{ENCODER_SWITCH, menu, selectItem, show_run},
    
	{INIT_OF_LINE, menu, do_nothing, show_menu},
    {END_OF_LINE, menu, do_nothing, show_menu},

	//Eventos de transiscion 
	{RUN, run, do_nothing, show_run},
	{SETTING, settings, do_nothing, show_settings},

    {NONE, menu, do_nothing, do_nothing}
};


state_edge_t settings[] = {
	//eventos de EventGenerator
    {ENCODER_RIGHT, settings, nextItem, show_menu},
    {ENCODER_LEFT, settings, prevItem, show_menu},
	{ENCODER_SWITCH, settings, selectItem, show_run},

	{INIT_OF_LINE, settings, do_nothing, show_settings},
    {END_OF_LINE, settings, do_nothing, show_settings},

	//Eventos de transiscion
	{MANUAL, set_manually, do_nothing, show_set_manually},
	{BLUETOOTH, bluetooth, activeBluetooth, show_bluetooth},
	
    {NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t bluetooth[] = {
    {ENCODER_SWITCH, settings, do_nothing, show_settings},
    {NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t set_manually[] = {
	//Eventos de EventGenerator
	{ENCODER_RIGHT, set_manually, nextItem, show_set_manually},
	{ENCODER_LEFT, set_manually, prevItem, show_set_manually},	
	{ENCODER_SWITCH, set_manually, selectItem, show_set_manually},

	{INIT_OF_LINE, set_manually, do_nothing, show_set_manually},
	{END_OF_LINE, set_manually, do_nothing, show_set_manually},

	//Eventos de transiscion
	{EDIT_PARTS, edit_parts, do_nothing, show_part_n},
	{ADD_PART, set_manually, do_nothing, show_set_manually},
	{DELETE_PART, set_manually, do_nothing, show_set_manually},

	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t edit_parts[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, edit_parts, nextItem, show_part_n},
	{ENCODER_LEFT, edit_parts, prevItem, show_part_n},
	{ENCODER_SWITCH, edit_parts, selectItem, show_part_n},

	{INIT_OF_LINE, edit_parts, do_nothing, show_set_manually},
	{END_OF_LINE, edit_parts, do_nothing, show_set_manually},

	//Eventos de transiscion
	{SELEC_X0, selec_x0, do_nothing, do_nothing},
	{SELEC_XF, selec_xf, do_nothing, do_nothing},
	{SELEC_DELTA_T, selec_delta_t, do_nothing, do_nothing},
	{SELEC_VEL, selec_vel, do_nothing, do_nothing},
	

    {NONE, estado_init, do_nothing, do_nothing}
};

//TODO: Implementar los estados de seleccion de valores
state_edge_t selec_x0[] = {

	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t selec_xf[] = {

	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t selec_delta_t[] = {

	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t selec_vel[] = {

	{NONE, estado_init, do_nothing, do_nothing}
};


//TODO: Implementar los estados de run
state_edge_t run[] = {
    {ENCODER_SWITCH, menu, do_nothing, show_menu},
    {NONE, estado_init, do_nothing, do_nothing}
};



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static menu_items_t * currentStateItem;

static menu_items_t main_menu_items = {{{0, RUN, "Run", 3},
									   {1, SETTING, "Settings", 8}}, 
									   0, 2};

static menu_items_t setting_items = {{{0, MANUAL, "Set manually", 12},
										  {1, BLUETOOTH, "Bluetooth", 9},
										  {2, BACK, "Back", 4}}, 
										  0, 3};

static menu_items_t set_manually_items = {{{0, EDIT_PARTS, "Edit parts", 9},
										  {1, ADD_PART, "Add part", 8},
										  {2, DELETE_PART, "Delete part", 11},
										  {3, BACK, "Back", 11}}, 
										  0, 4};

static menu_items_t edit_parts_items = {{{0, SELEC_X0, "Select X0", 9},
										  {1, SELEC_XF, "Select Xf", 9},
										  {2, SELEC_DELTA_T, "Time", 4},
										  {3, SELEC_VEL, "Velocity", 8},
										  {4, BACK, "Back", 4}},
										  0, 5};


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
static void nextMenuItem(void){
	currentStateItem->item_selec++;
	if(currentStateItem->item_selec >= currentStateItem->item_cant){
		currentStateItem->item_selec = 0;
	}
}

static void prevMenuItem(void){
	if(currentStateItem->item_selec == 0){
		currentStateItem->item_selec = currentStateItem->item_cant - 1;
	}
	else{
		currentStateItem->item_selec--;
	}
}

static void selectMenuItem(void){
	EG_addExternEvent((events_t)(currentStateItem->item[currentStateItem->item_selec].item_event_select));
}

/*******************************************************************************
 * 						Setting FUNCTIONS
 ******************************************************************************/


//---------------------Copilot functions---------------------
static void show_menu(void) {
   
}

static void show_run(void) {
}

static void show_settings(void) {
}

static void show_bluetooth(void) {
}

static void show_set_manually(void) {
}

static void show_part_n(void) {
}

static void show_add_part(void) {
}

static void show_delete_part(void) {
}
