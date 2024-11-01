/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsmTable.h"
#include "Display.h"
#include "screen.h"

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

extern state_edge_t selec_distances[];
extern state_edge_t selec_delta_t[];
extern state_edge_t selec_vel[];

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
enum eventos{
	RUN_ = 100,
	PAUSE_,
	FINISH,
	SETTING,
	BLUETOOTH,
	MANUAL,
	EDIT_PARTS,
	ADD_PART,
	DELETE_PART,
	SELEC_DIS,
	SELEC_DELTA_T,
	SELEC_VEL,
	X0,
	XF,
	RIGH,
	LEFT,
	OK_,
	DIGIT_0,
	DIGIT_1,
	DIGIT_2,
	DIGIT_3,
	BACK
};

//Items definitions
#define MAX_ITEMS 10


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct{
	uint8_t item_numer;
	uint8_t item_event_select;
	uint8_t cursor_pos_col;
	uint8_t cursor_pos_fil;
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

state_edge_t estado_init[] = {
	{ENCODER_RIGHT, menu, show_menu, show_menu},
    {ENCODER_LEFT, menu, show_menu, show_menu},
	{ENCODER_SWITCH, menu, show_menu, show_run},
    
	{INIT_OF_LINE, menu, show_menu, show_menu},
    {END_OF_LINE, menu, show_menu, show_menu},

    {NONE, menu, show_menu, do_nothing}
};

state_edge_t menu[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, menu, nextItem, show_menu},
    {ENCODER_LEFT, menu, prevItem, show_menu},
	{ENCODER_SWITCH, menu, selectItem, show_run},
    
	{INIT_OF_LINE, menu, do_nothing, show_menu},
    {END_OF_LINE, menu, do_nothing, show_menu},

	//Eventos de transiscion 
	{RUN_, run, show_run, show_run},
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
	{SELEC_DIS, selec_distances, do_nothing, do_nothing},
	{SELEC_DELTA_T, selec_delta_t, do_nothing, do_nothing},
	{SELEC_VEL, selec_vel, do_nothing, do_nothing},
	

    {NONE, estado_init, do_nothing, do_nothing}
};



state_edge_t selec_distances[] = {
	//eventos de EventGenerator
	{ENCODER_RIGHT, selec_distances, nextItem, show_part_n},
	{ENCODER_LEFT, selec_distances, prevItem, show_part_n},
	{ENCODER_SWITCH, selec_distances, selectItem, show_part_n},

	{INIT_OF_LINE, selec_distances, do_nothing, show_part_n},
	{END_OF_LINE, selec_distances, do_nothing, show_part_n},

	//Eventos de transiscion
	{X0, selec_distances, do_nothing, do_nothing},
	{XF, selec_distances, do_nothing, do_nothing},
	{RIGH, selec_distances, do_nothing, do_nothing},	
	{LEFT, selec_distances, do_nothing, do_nothing},
	{OK_, edit_parts, do_nothing, do_nothing},

	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t selec_delta_t[] = {
	//eventos de EventGenerator
	{ENCODER_RIGHT, selec_delta_t, nextItem, show_part_n},
	{ENCODER_LEFT, selec_delta_t, prevItem, show_part_n},
	{ENCODER_SWITCH, selec_delta_t, selectItem, show_part_n},

	{INIT_OF_LINE, selec_delta_t, do_nothing, show_part_n},
	{END_OF_LINE, selec_delta_t, do_nothing, show_part_n},

	//Eventos de transiscion
	{DIGIT_0, selec_delta_t, do_nothing, do_nothing},
	{DIGIT_1, selec_delta_t, do_nothing, do_nothing},
	{DIGIT_2, selec_delta_t, do_nothing, do_nothing},
	{DIGIT_3, selec_delta_t, do_nothing, do_nothing},
	{OK_, edit_parts, do_nothing, do_nothing},

	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t selec_vel[] = {

	//eventos de EventGenerator
	{ENCODER_RIGHT, selec_vel, nextItem, show_part_n},
	{ENCODER_LEFT, selec_vel, prevItem, show_part_n},
	{ENCODER_SWITCH, selec_vel, selectItem, show_part_n},

	{INIT_OF_LINE, selec_vel, do_nothing, show_part_n},
	{END_OF_LINE, selec_vel, do_nothing, show_part_n},

	//Eventos de transiscion
	{DIGIT_0, selec_vel, do_nothing, do_nothing},
	{DIGIT_1, selec_vel, do_nothing, do_nothing},
	{DIGIT_2, selec_vel, do_nothing, do_nothing},
	{DIGIT_3, selec_vel, do_nothing, do_nothing},
	{OK_, edit_parts, do_nothing, do_nothing},

	{NONE, estado_init, do_nothing, do_nothing}
};


//TODO: Implementar los estados de run
state_edge_t run[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, run, nextItem, show_run},
    {ENCODER_LEFT, run, prevItem, show_run},
	{ENCODER_SWITCH, run, selectItem, show_run},
    
	{INIT_OF_LINE, run, do_nothing, show_run},
    {END_OF_LINE, run, do_nothing, show_run},

	//Eventos de transiscion
	{PAUSE_, run, do_nothing, do_nothing},
	{FINISH, run, do_nothing, do_nothing},
	{BACK, menu, do_nothing, do_nothing},


    {NONE, estado_init, do_nothing, do_nothing}
};



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static menu_items_t * currentStateItem;

static menu_items_t main_menu_items = {{{0, RUN_, RUN_COL, RUN_FIL},
									   {1, SETTING, SETTING_COL, SETTING_FIL}},
									   0, 2};

static menu_items_t run_items = {{{0, PAUSE_, PAUSE_COL, PAUSE_FIL},
									{1, FINISH, FINISH_COL, FINISH_FIL},
								  {2, BACK, BACK_COL, BACK_FIL}},
								  0, 2};

static menu_items_t setting_items = {{{0, MANUAL, MANUAL_COL, MANUAL_FIL},
										  {1, BLUETOOTH, BLUETOOTH_COL, BLUETOOTH_FIL},
										  {2, BACK, BACK_COL, BACK_FIL}},
										  0, 3};

static menu_items_t set_manually_items = {{{0, EDIT_PARTS,EDIT_PARTS_COL, EDIT_PARTS_FIL},
										  {1, ADD_PART, ADD_PART_COL, ADD_PART_FIL},
										  {2, DELETE_PART, DEL_COL, DEL_FIL},
										  {3, BACK, BACK_COL, BACK_FIL}}, 
										  0, 4};

static menu_items_t edit_parts_items = {{{0, SELEC_DIS, SEL_DIS_COL, SEL_DIS_FIL},
										  {1, SELEC_DELTA_T, SEL_DELTA_COL, SEL_DELTA_FIL},
										 {2, BACK, BACK_COL, BACK_FIL}}, 
										  0, 3};

static menu_items_t selec_dis_items = {{{0, X0, X0_COL, X0_FIL},
										{1, XF, XF_COL, XF_FIL},
										{2, LEFT, LEFT_COL, LEFT_FIL},
										{3, RIGH, RIGHT_COL, RIGHT_FIL},
										{4, OK_, OK_COL, OK_FIL}},
										0, 5};

static menu_items_t selec_numbers = {{{0, DIGIT_0, DIGIT_0_COL, DIGIT_0_FIL},
									{1, DIGIT_1, DIGIT_1_COL, DIGIT_1_FIL},
									{2, DIGIT_2, DIGIT_2_COL, DIGIT_2_FIL},
									{3, DIGIT_3, DIGIT_3_COL, DIGIT_3_FIL},
									{4, OK_, OK_COL, OK_FIL}},
									0, 5};

static uint8_t listOfOptions[4] = {0, 1, 2, 3};

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
 * 						ITEMS FUNCTIONS
 ******************************************************************************/
static void nextItem(void){
	currentStateItem->item_selec++;
	if(currentStateItem->item_selec >= currentStateItem->item_cant){
		currentStateItem->item_selec = 0;
	}
	show_curs(currentStateItem->item->cursor_pos_col, currentStateItem->item->cursor_pos_fil);
}

static void prevItem(void){
	if(currentStateItem->item_selec == 0){
		currentStateItem->item_selec = currentStateItem->item_cant - 1;
	}
	else{
		currentStateItem->item_selec--;
	}
	show_curs(currentStateItem->item->cursor_pos_col, currentStateItem->item->cursor_pos_fil);
}

static void selectItem(void){
	EG_addExternEvent((events_t)(currentStateItem->item[currentStateItem->item_selec].item_event_select));
}

/*******************************************************************************
 * 						menu FUNCTIONS
 ******************************************************************************/
static void show_menu(void){
	currentStateItem = &main_menu_items;
	//show_screen(currentStateItem->item[currentStateItem->item_selec].name, BLANK);
	show_screen(MENU_TITLE, MENU_LINE1);
	
}


/*******************************************************************************
 * 						Setting FUNCTIONS
 ******************************************************************************/
static void activeBluetooth(void){

}


//---------------------Copilot functions---------------------


static void show_run(void) {
	currentStateItem = &run_items;
	show_screen(RUN, PAUSE_FINISH);	
}

static void show_settings(void) {
	currentStateItem = &setting_items;
	show_screen(BT_OFF, SET_MAN);
}

static void show_bluetooth(void) {
	static bool bt = false;
	bt = !bt;
	if(bt){
		show_screen(BT_ON,BLANK);
		//TODO: Implementar la activacion del bluetooth
	}
	else{
		show_screen(BT_OFF,SET_MAN);
	}
}

static void show_set_manually(void) {
	currentStateItem = &set_manually_items;
	show_screen(PARTS, ADD_DEL);
}



static void show_part_n(void) {
}

static void show_add_part(void) {
}

static void show_delete_part(void) {
}
