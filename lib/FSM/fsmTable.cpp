/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsmTable.h"
#include "Display.h"
#include "screen.h"
#include "EventGenerator.h"
#include "sliderCamara.h"



/*******************************************************************************
 * Foward declarations States
 ******************************************************************************/
extern state_edge_t estado_init[];

extern state_edge_t menu[];
extern state_edge_t settings[];
extern state_edge_t run[];

extern state_edge_t bluetooth[];
extern state_edge_t set_manually[];
extern state_edge_t set_parts[];

extern state_edge_t edit_distances[];
extern state_edge_t edit_times[];	

extern state_edge_t selec_x[];
extern state_edge_t selec_delta_t[];

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
enum eventos{
	RUN_ = 100,
	PAUSE_RESUME,
	FINISH,
	RESTART,
	SETTING,
	BLUETOOTH,
	MANUAL,
	SET_PARTS,
	ADD_PART,
	DELETE_PART,
	SET_DIS,
	SET_TIMES,
	RIGH,
	LEFT,
	OK_,
	BACK
};

//Items definitions
#define MAX_ITEMS 10

//Constant steps 
#define STEP 		100
#define TIME_STEP_S	5
#define VACIO		(-1)

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

typedef struct{
	int64_t x0;
	int64_t xf;
	int64_t tiempo;
}tramo_t;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void do_nothing(void);

static void show_menu(void);
static void show_run(void);
static void show_settings(void);
static void show_bluetooth(void);
static void show_set_manually(void);
static void show_set_parts(void);
static void show_edit_dis(void);
static void show_edit_time(void);



//Items selector
static void nextItem(void);
static void prevItem(void);
static void selectItem(void);

//Settings FUNCTIONS
static void activeBluetooth(void);

//set manually and Selec part to edit
static void add_part(void);
static void delete_part(void);

//Set parts FUNCTIONS
static void nextPart(void);
//static void prevPart(void);
//static void selectPart(void);

//rutinas de select x0 y xf
static void settingMotor(void);
static void increment_x(void);	
static void decrement_x(void);
static void stop_fin_x(void);
static void stop_ini_x(void);

//rutinas de select delta T
static void increment_time(void);
static void decrement_time(void);
static void next_time(void);

//rutinas de run
static void run_slider(void);
static void restart(void);
static void pause_resume(void);
static void finish(void);

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

state_edge_t estado_init[] = {
	{ENCODER_RIGHT, menu, show_menu, show_menu},
    {ENCODER_LEFT, menu, show_menu, show_menu},
	{ENCODER_SWITCH, menu, show_menu, show_menu},
    
	{INIT_OF_LINE, menu, show_menu, show_menu},
    {END_OF_LINE, menu, show_menu, show_menu},

    {NONE, menu, show_menu, show_menu}
};

state_edge_t menu[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, menu, nextItem, show_menu},
    {ENCODER_LEFT, menu, prevItem, show_menu},
	{ENCODER_SWITCH, menu, selectItem, show_menu},
    
	{INIT_OF_LINE, menu, do_nothing, show_menu},
    {END_OF_LINE, menu, do_nothing, show_menu},

	//Eventos de transiscion 
	{RUN_, run, show_run, show_run},
	{SETTING, settings, show_settings, show_settings},

    {NONE, menu, do_nothing, show_menu}
};


state_edge_t settings[] = {
	//eventos de EventGenerator
    {ENCODER_RIGHT, settings, nextItem, show_settings},
    {ENCODER_LEFT, settings, prevItem, show_settings},
	{ENCODER_SWITCH, settings, selectItem, show_settings},

	{INIT_OF_LINE, settings, do_nothing, show_settings},
    {END_OF_LINE, settings, do_nothing, show_settings},

	//Eventos de transiscion
	{MANUAL, set_manually, show_set_manually, show_set_manually},
	{BLUETOOTH, bluetooth, activeBluetooth, show_bluetooth},
	{BACK, menu, show_menu, show_menu},
    {NONE, settings, do_nothing, show_settings}
};

state_edge_t bluetooth[] = {
    {ENCODER_SWITCH, settings, do_nothing, show_settings},
    {NONE, bluetooth, do_nothing, do_nothing}
};

state_edge_t set_manually[] = {
	//Eventos de EventGenerator
	{ENCODER_RIGHT, set_manually, nextItem, show_set_manually},
	{ENCODER_LEFT, set_manually, prevItem, show_set_manually},	
	{ENCODER_SWITCH, set_manually, selectItem, show_set_manually},

	{INIT_OF_LINE, set_manually, do_nothing, show_set_manually},
	{END_OF_LINE, set_manually, do_nothing, show_set_manually},

	//Eventos de transiscion
	{SET_PARTS, set_parts, do_nothing, show_set_parts},
	{ADD_PART, set_manually, add_part, show_set_manually},
	{DELETE_PART, set_manually, delete_part, show_set_manually},
	{BACK, settings, show_settings, show_settings},
	{NONE, set_manually, do_nothing, show_set_manually}
};

state_edge_t set_parts[] = {
	//Eventos de EventGenerator
	{ENCODER_RIGHT, set_parts, nextItem, show_set_parts},
	{ENCODER_LEFT, set_parts, prevItem, show_set_parts},	
	{ENCODER_SWITCH, set_parts, selectItem, show_set_parts},

	{INIT_OF_LINE, set_parts, do_nothing, do_nothing},
	{END_OF_LINE, set_parts, do_nothing, do_nothing},

	//Eventos de transiscion
	{SET_TIMES, edit_times, do_nothing, show_edit_time},
	{SET_DIS, edit_distances, do_nothing, show_edit_dis},
	{BACK, set_manually, show_set_manually, show_set_manually},

	{NONE, set_parts, do_nothing, show_set_parts}
};

state_edge_t edit_distances[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, edit_distances, increment_x, show_edit_dis},
	{ENCODER_LEFT, edit_distances, decrement_x, show_edit_dis},
	{ENCODER_SWITCH, edit_distances, nextPart, show_edit_dis},

	{INIT_OF_LINE, edit_distances, stop_fin_x, show_edit_dis},
	{END_OF_LINE, edit_distances, stop_ini_x, show_edit_dis},

	//Eventos de transiscion
	{BACK, set_parts, do_nothing, show_set_parts},
	{NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t edit_times[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, edit_times, increment_time, show_edit_time},
	{ENCODER_LEFT, edit_times, decrement_time, show_edit_time},
	{ENCODER_SWITCH, edit_times, next_time, show_edit_time},

	{INIT_OF_LINE, edit_times, do_nothing, show_edit_time},
	{END_OF_LINE, edit_times, do_nothing, show_edit_time},

	//Eventos de transiscion
	{BACK, set_parts, do_nothing, show_set_parts},
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
	{PAUSE_RESUME, run, pause_resume, show_run},
	{RESTART, run, restart, show_run},
	{FINISH, menu, finish, show_menu},
	{BACK, menu, do_nothing, show_menu},

    {NONE, run, do_nothing, do_nothing}
};



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static menu_items_t * currentStateItem;

static menu_items_t main_menu_items = {{{0, RUN_, RUN_COL, RUN_FIL},
									    {1, SETTING, SETTING_COL, SETTING_FIL}},
									     0, 2};

static menu_items_t run_items = {{{0, PAUSE_RESUME, PAUSE_COL, PAUSE_FIL},
								  {1, FINISH, FINISH_COL, FINISH_FIL},
								  {2, RESTART, RESTART_COL, RESTART_FIL}},
								   0, 3};

static menu_items_t setting_items = {{{0, MANUAL, MANUAL_COL, MANUAL_FIL},
									  {1, BLUETOOTH, BLUETOOTH_COL, BLUETOOTH_FIL},
									  {2, BACK, BACK_COL, BACK_FIL}},
									   0, 3};

static menu_items_t set_manually_items = {{{0, SET_PARTS, EDIT_PARTS_COL, EDIT_PARTS_FIL},
										   {1, ADD_PART, ADD_PART_COL, ADD_PART_FIL},
										   {2, DELETE_PART, DEL_COL, DEL_FIL},
										   {3, BACK, BACK_COL, BACK_FIL}}, 
										    0, 4};

static menu_items_t set_parts_items = {{{0, SET_TIMES, TIME_BK_COL, TIME_BK_FIL},
										{1, SET_DIS, DISTANCES_COL, DISTANCES_FIL},
										{2, BACK, BACK_COL, BACK_FIL}}, 
										 0, 3};


static uint8_t part_to_edit = 0;
static uint64_t points[5+1] = {0};						
static uint64_t times[5] = {0};
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
	Serial.println(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col);
	
}

static void prevItem(void){
	if(currentStateItem->item_selec == 0){
		currentStateItem->item_selec = currentStateItem->item_cant - 1;
	}
	else{
		currentStateItem->item_selec--;
	}
	Serial.println(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col);

}

static void selectItem(void){
	EG_addExternEvent((events_t)(currentStateItem->item[currentStateItem->item_selec].item_event_select));
}

/*******************************************************************************
 * 						menu FUNCTIONS
 ******************************************************************************/
static void show_menu(void){
	currentStateItem = &main_menu_items;
	show_screen(MENU_TITLE, MENU_LINE1);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
}

/*******************************************************************************
 * 						Setting FUNCTIONS
 ******************************************************************************/
static void show_settings(void) {
	currentStateItem = &setting_items;
	show_screen(SET_MAN, BT_OFF);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
}


/*******************************************************************************
 * 						bluetooth FUNCTIONS
 ******************************************************************************/
static void show_bluetooth(void) {
	static bool bt = false;
	bt = !bt;
	if(bt){
		show_screen(BT_ON,BLANK);
		show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);

		//TODO: Implementar la activacion del bluetooth
	}
	else{
		show_screen(BT_OFF,SET_MAN);
		show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);

	}
}

static void activeBluetooth(void){

}


/*******************************************************************************
 * 						Set Manually FUNCTIONS
 ******************************************************************************/
static void show_set_manually(void) {
	currentStateItem = &set_manually_items;
	show_screen(PARTS, ADD_DEL);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
	disp_write_number(getCantTramos(), CANT_PART_COL, CANT_PART_FIL);
}

static void add_part(void) {
	if(getCantTramos() < 5){
		modifyNumTramos(ADD);
		//tramo por defecto
		modifyMovement(getCantTramos()-1, 0, 0, 0);
	}
}

static void delete_part(void) {
	modifyNumTramos(ERASE);
}

/*******************************************************************************
 * 						set parts FUNCTIONS
 ******************************************************************************/
static void show_set_parts(void) {
	currentStateItem = &set_parts_items;
	show_screen(TIME_BACK, POSITIONS);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
}


/*******************************************************************************
 * 						edit distancies FUNCTIONS
 ******************************************************************************/
static void show_edit_dis(void) {
	setMotorEnable(ON);
	setState(SETTING_MOTOR);

	show_screen(DISTANCES_n, BLANK);
	disp_write_number(part_to_edit, DIS_COL+2, DIS_FIL);
	//disp_write_number(getStepCurrent(), DIS_COL+5, DIS_FIL);
}

static void settingMotor(){

}

static void nextPart(void){
	points[part_to_edit] = getStepCurrent();
	if(part_to_edit < getCantTramos()){
		//quedan tramos por editar
		part_to_edit++;
	}
	else{
		//todos los tramos fueron editados
		setState(STOPPED);
		setMotorEnable(OFF);
		part_to_edit = 0;
		for(int i = 0; i < getCantTramos(); i++){
			modifyMovement(i, points[i], points[i+1], 0);
		}
		EG_addExternEvent((events_t)BACK);
	}
}

static void increment_x(void) {	
	setMotorDir(ANTIHORARIO);	//antihorario
	setMoreSteps(STEP);
}

static void decrement_x(void) {	
	setMotorDir(HORARIO);	//horario
	setMoreSteps(STEP);
}

static void stop_fin_x(void) {
	if(getMotorDir() == ANTIHORARIO){
		setStepRemaining(0);
	}
}

static void stop_ini_x(void) {
	if(getMotorDir() == HORARIO){
		setStepRemaining(0);
		setStepCurrent(0);
	}
}

/*******************************************************************************
 * 						selec time FUNCTIONS
 ******************************************************************************/
static void show_edit_time(void) {
	show_screen(TIME_SELECT_0, BLANK);
	disp_write_number(part_to_edit+1, DIS_COL+5, DIS_FIL);
	disp_write_number(times[part_to_edit], TIME_COL+7, TIME_FIL);

}

static void increment_time(void) {
	if(	times[part_to_edit] + TIME_STEP_S < 9999){
		times[part_to_edit] += TIME_STEP_S;
	}
	else{
		times[part_to_edit] = 9999;
	}
		
}

static void decrement_time(void) {
	if(times[part_to_edit] > TIME_STEP_S ){
		times[part_to_edit] -= TIME_STEP_S;
	}
	else{
		times[part_to_edit] = 0;
	}

}

static void next_time(void) {
	if(part_to_edit < getCantTramos()-1){
		part_to_edit++;
	}
	else{
		part_to_edit = 0;
		for(int i = 0; i < getCantTramos(); i++){
			modifyMovement(i+1, points[i], points[i+1], times[i]);
		}
		EG_addExternEvent((events_t)BACK);
	}
}	

/*******************************************************************************
 * 						run FUNCTIONS
 ******************************************************************************/
/*******************************************************************************
 * 						Run FUNCTIONS
 ******************************************************************************/
static void show_run(void) {
	currentStateItem = &run_items;

	switch (getStateSlider())
	{
	case PAUSED:
		show_screen(RUN, RESUME_FINISH);
		break;
	case RUNNING:
		show_screen(RUN, PAUSE_FINISH);	
		break;
	//case FINISHED:
		/* code */
	//	break;
	default:
		show_screen(RUN, BLANK);	
		break;
	}
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
	//disp_write_number(getCurrStep(), 0, 1);
}

static void restart(void){
	setState(RUNNING);
}

static void pause_resume(void){
	if(getStateSlider() == RUNNING){
		setState(PAUSED);
	}
	else if(getStateSlider() == PAUSED){
		setState(RUNNING);
	}
}	

static void finish(void){
	setState(STOPPED);
}

static void run_slider(void){

}