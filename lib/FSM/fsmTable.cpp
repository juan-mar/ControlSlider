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
	PAUSE_,
	FINISH,
	SETTING,
	BLUETOOTH,
	MANUAL,
	SET_PARTS,
	ADD_PART,
	DELETE_PART,
	SET_DIS,
	SET_TIMES,
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
static void show_select_delta_t(void);



//Items selector
static void nextItem(void);
static void prevItem(void);
static void selectItem(void);

//Settings FUNCTIONS
static void activeBluetooth(void);

//set manually and Selec part to edit
static void selectPart(void);
static void add_part(void);
static void delete_part(void);

//rutinas de select x0 y xf
static void show_selec_x(void);
static void select_x(void);
static void increment_x(void);	
static void decrement_x(void);
static void stop_limit_x(void);


static void run_slider(void);

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
	{ADD_PART, set_manually, do_nothing, show_set_manually},
	{DELETE_PART, set_manually, do_nothing, show_set_manually},
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
	{ENCODER_RIGHT, edit_distances, nextItem, show_edit_dis},
	{ENCODER_LEFT, edit_distances, prevItem, show_edit_dis},
	{ENCODER_SWITCH, selec_x, selectItem, show_edit_dis},

	{INIT_OF_LINE, edit_distances, do_nothing, show_edit_dis},
	{END_OF_LINE, edit_distances, do_nothing, show_edit_dis},

	//Eventos de transiscion
	{BACK, set_parts, do_nothing, show_set_parts},
	
    {NONE, estado_init, do_nothing, do_nothing}
};

state_edge_t selec_x[] = {
	//eventos de EventGenerator
	{ENCODER_RIGHT, selec_x, increment_x, show_selec_x},
	{ENCODER_LEFT, selec_x, decrement_x, show_selec_x},
	{ENCODER_SWITCH, edit_distances, select_x, show_edit_dis},

	{INIT_OF_LINE, selec_x, stop_limit_x0, show_selec_x},
	{END_OF_LINE, selec_x, stop_limit_x0, show_selec_x},

	//Eventos de transiscion
	
	{NONE, selec_x, do_nothing, do_nothing}
};

state_edge_t edit_times[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, edit_parts, nextItem, show_edit_part},
	{ENCODER_LEFT, edit_parts, prevItem, show_edit_part},
	{ENCODER_SWITCH, edit_parts, selectItem, show_edit_part},

	{INIT_OF_LINE, edit_parts, do_nothing, show_edit_part},
	{END_OF_LINE, edit_parts, do_nothing, show_edit_part},

	//Eventos de transiscion
	
    {NONE, estado_init, do_nothing, do_nothing}
};


state_edge_t selec_delta_t[] = {
	//eventos de EventGenerator
	{ENCODER_RIGHT, selec_delta_t, nextItem, show_part_to_edit},
	{ENCODER_LEFT, selec_delta_t, prevItem, show_part_to_edit},
	{ENCODER_SWITCH, selec_delta_t, selectItem, show_part_to_edit},

	{INIT_OF_LINE, selec_delta_t, do_nothing, show_part_to_edit},
	{END_OF_LINE, selec_delta_t, do_nothing, show_part_to_edit},

	//Eventos de transiscion
	{DIGIT_0, selec_delta_t, do_nothing, do_nothing},
	{DIGIT_1, selec_delta_t, do_nothing, do_nothing},
	{DIGIT_2, selec_delta_t, do_nothing, do_nothing},
	{DIGIT_3, selec_delta_t, do_nothing, do_nothing},
	{OK_, edit_parts, do_nothing, do_nothing},

	{NONE, estado_init, do_nothing, do_nothing}
};




//TODO: Implementar los estados de run
state_edge_t run[] = {
    //Eventos de EventGenerator
	{ENCODER_RIGHT, run, nextItem, run_slider},
    {ENCODER_LEFT, run, prevItem, run_slider},
	{ENCODER_SWITCH, run, selectItem, run_slider},
    
	{INIT_OF_LINE, run, do_nothing, run_slider},
    {END_OF_LINE, run, do_nothing, run_slider},

	//Eventos de transiscion
	{PAUSE_, run, do_nothing, run_slider},
	{FINISH, run, do_nothing, run_slider},
	{BACK, menu, do_nothing, run_slider},


    {NONE, estado_init, do_nothing, run_slider}
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



static menu_items_t selec_numbers = {{{0, DIGIT_0, DIGIT_0_COL, DIGIT_0_FIL},
									{1, DIGIT_1, DIGIT_1_COL, DIGIT_1_FIL},
									{2, DIGIT_2, DIGIT_2_COL, DIGIT_2_FIL},
									{3, DIGIT_3, DIGIT_3_COL, DIGIT_3_FIL},
									{4, OK_, OK_COL, OK_FIL}},
									0, 5};

static uint8_t part_to_edit = 0;
static tramo_t tramos[5] = {{0,100,10},
							{VACIO,VACIO,VACIO},
							{VACIO,VACIO,VACIO},
							{VACIO,VACIO,VACIO},
							{VACIO,VACIO,VACIO}};

							


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
 * 						Run FUNCTIONS
 ******************************************************************************/
static void show_run(void) {
	currentStateItem = &run_items;
	show_screen(RUN, PAUSE_FINISH);	
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
}

static void add_part(void) {
	if(getCantTramos() < 5){
		modifyNumTramos(ADD);
		tramos[getCantTramos()-1].x0 = tramos[getCantTramos()-2].xf;
		tramos[getCantTramos()-1].xf = tramos[getCantTramos()-1].x0 + 100;	
		tramos[getCantTramos()-1].tiempo = 10;
		modifyMovement(getCantTramos()-1, VACIO, VACIO, VACIO);	
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
static void show_edit_part(void) {

	currentStateItem = &edit_parts_items;
	show_screen(TIME_BACK, POSITIONS);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
	//Upload valores del tramo a editar

}

/*******************************************************************************
 * 						selec X0 y Xf FUNCTIONS
 ******************************************************************************/
//------------------------------------X0-----------------------------------------
static void show_selec_x0(void) {
	show_screen(TIME_BACK, POSITIONS);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
	disp_write_number(tramos[part_to_edit].x0, X0_COL + 4, X0_FIL);
	disp_write_number(tramos[part_to_edit].tiempo, SEL_TIME_COL + 3, SEL_TIME_FIL);
}	

static void select_x0(void) {
	if(part_to_edit > 0){
		tramos[part_to_edit-1].xf = tramos[part_to_edit].x0;
		if(tramos[part_to_edit].x0 > tramos[part_to_edit-1].xf){
			//Se agranda el tramo anterior por ser X0_actual > Xf_prev
			//verifico que tiempo en el tramo sea el correcto
			uint64_t delta_time_steps = (1000*1000*(tramos[part_to_edit-1].xf - tramos[part_to_edit-1].x0))/tramos[part_to_edit-1].tiempo;
			if(delta_time_steps < MAX_VEL){
				delta_time_steps = MAX_VEL;
				tramos[part_to_edit-1].tiempo = (1000*1000*(tramos[part_to_edit-1].xf - tramos[part_to_edit-1].x0))/MAX_VEL;			
			}		
		}
		modifyMovement(part_to_edit, tramos[part_to_edit-1].x0, tramos[part_to_edit-1].xf, tramos[part_to_edit-1].tiempo);
	}
	else{
		modifyMovement(part_to_edit, tramos[part_to_edit].x0, tramos[part_to_edit].xf, tramos[part_to_edit].tiempo);
	}
}

static void increment_x0(void) {	
	setMotorDir(ANTIHORARIO);	//antihorario
	tramos[part_to_edit].x0 += STEP;
	setMoreSteps(STEP);
}

static void decrement_x0(void) {	
	setMotorDir(HORARIO);	//horario
	if(tramos[part_to_edit].x0 > STEP){
		tramos[part_to_edit].x0 -= STEP;
		setMoreSteps(STEP);
	}
	else{
		setStepRemainig(tramos[part_to_edit].x0);
		tramos[part_to_edit].x0 = 0;
	}
}

static void stop_limit_x0(void) {
	uint64_t steps = getStepRemainig();
	setStepRemainig(0);
	tramos[part_to_edit].x0 -= steps;
	//otra opcion
	//tramos[part_to_edit].x0 = getCurrentStep();
}

//------------------------------------Xf-----------------------------------------
static void show_selec_xf(void) {
	show_screen(TIME_BACK, POSITIONS);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);
	disp_write_number(tramos[part_to_edit].xf, XF_COL + 4, XF_FIL);
	disp_write_number(tramos[part_to_edit].tiempo, SEL_TIME_COL + 3, SEL_TIME_FIL);
}

static void select_xf(void) {
	if(part_to_edit > 0 && part_to_edit < getCantTramos()-1){
		//no es el ultimo tramo
		tramos[part_to_edit+1].x0 = tramos[part_to_edit].xf;
		if(tramos[part_to_edit].xf < tramos[part_to_edit+1].x0){
			//Se agranda el tramo siguiente por ser Xf_actual < X0_next
			//verifico que tiempo en el tramo sea el correcto
			uint64_t delta_time_steps = (1000*1000*(tramos[part_to_edit+1].xf - tramos[part_to_edit+1].x0))/tramos[part_to_edit+1].tiempo;
			if(delta_time_steps < MAX_VEL){
				delta_time_steps = MAX_VEL;
				tramos[part_to_edit+1].tiempo = (1000*1000*(tramos[part_to_edit+1].xf - tramos[part_to_edit+1].x0))/MAX_VEL;			
			}
		}
		modifyMovement(part_to_edit, tramos[part_to_edit+1].x0, tramos[part_to_edit+1].xf, tramos[part_to_edit+1].tiempo);
	}
	//es el ultimo tramo
	//verifico que tiempo en el tramo sea el correcto
	uint64_t delta_time_steps = (1000*1000*(tramos[part_to_edit].xf - tramos[part_to_edit].x0))/tramos[part_to_edit].tiempo;
	if(delta_time_steps < MAX_VEL){
		delta_time_steps = MAX_VEL;
		tramos[part_to_edit].tiempo = (1000*1000*(tramos[part_to_edit].xf - tramos[part_to_edit].x0))/MAX_VEL;			
	}
	modifyMovement(part_to_edit, tramos[part_to_edit].x0, tramos[part_to_edit].xf, tramos[part_to_edit].tiempo);
}

static void increment_xf(void) {
	tramos[part_to_edit].xf += STEP;
	setMoreSteps(STEP);
	setMotorDir(ANTIHORARIO);	
}

static void decrement_xf(void){
	if(tramos[part_to_edit].xf - STEP > tramos[part_to_edit].x0){
		tramos[part_to_edit].xf -= STEP;
		setMoreSteps(STEP);
	}
	else{
		//Si quiero decrementar menos de lo que ya tengo en x0 no puedo (do_nothing)
		//setStepRemainig(tramos[part_to_edit].xf);
		//tramos[part_to_edit].xf = tramos[part_to_edit].x0;
	}
	setMotorDir(HORARIO);	
}

static void stop_limit_xf(void) {
	uint64_t steps = getStepRemainig();
	setStepRemainig(0);
	tramos[part_to_edit].xf -= steps;
	//otra opcion
	//tramos[part_to_edit].xf = getCurrentStep();
}

/*******************************************************************************
 * 						selec delta T FUNCTIONS
 ******************************************************************************/
//TODO: Implementar las funciones de seleccion de delta T
static void show_select_delta_t(void) {
	currentStateItem = &selec_numbers;
	show_screen(BLANK, BLANK);
	show_curs(currentStateItem->item[currentStateItem->item_selec].cursor_pos_col, 
				currentStateItem->item[currentStateItem->item_selec].cursor_pos_fil);

}	

/*******************************************************************************
 * 						run FUNCTIONS
 ******************************************************************************/
static void run_slider(void){
				
	




}