
#ifndef SCREEN_H
#define SCREEN_H

// Define screen positions for cursor placement
enum cursor_col{COL0 = 0, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14, COL15};
enum cursor_fil{FILA0 = 0, FILA1};

// Define positions for menu items
#define PAUSE_COL       0
#define PAUSE_FIL       0
#define FINISH_COL      1
#define FINISH_FIL      1
#define BACK_COL        2
#define BACK_FIL        2

#define SEL_DIS_COL     0
#define SEL_DIS_FIL     0
#define LEFT_COL        2
#define LEFT_FIL        2
#define RIGHT_COL       3
#define RIGHT_FIL       3
#define OK_COL          4
#define OK_FIL          4
#define DIGIT_0_COL     0
#define DIGIT_0_FIL     0
#define DIGIT_1_COL     1
#define DIGIT_1_FIL     1
#define DIGIT_2_COL     2
#define DIGIT_2_FIL     2
#define DIGIT_3_COL     3
#define DIGIT_3_FIL     3


// PANTALLA DE INICIO
#define MENU_TITLE       "Camera Slider   "
#define MENU_LINE1       " Run   Settings "           
#define LINE2            " Continue    End"
#define RUN_COL         0
#define RUN_FIL         1
#define SETTING_COL     6
#define SETTING_FIL     1

//PANTALLA DE CONFIGURACION
#define BT_ON            " Bluetooth   ON "
#define BT_OFF           " Bluetooth   OFF"
#define SET_MAN          " Set Manually  B"
#define MANUAL_COL      0
#define MANUAL_FIL      0
#define BLUETOOTH_COL   0
#define BLUETOOTH_FIL   1
#define BACK_COL        14
#define BACK_FIL        0


// SELECT PARTS
#define PARTS            " Edit Part:    B"
#define ADD_DEL          " Add         Del"
#define EDIT_PARTS_COL  0
#define EDIT_PARTS_FIL  0
#define ADD_PART_COL    0
#define ADD_PART_FIL    1
#define DEL_COL         12
#define DEL_FIL         1
#define SEL_PART_COL    11
#define SEL_PART_FIL    0
#define NUN_PARTS_COL   12


// EDIT PART
#define TIME_BACK        " T:    s       B"
#define POSITIONS        " Xo:     Xf:    "
#define X0_COL          0
#define X0_FIL          1
#define XF_COL          8
#define XF_FIL          1
#define SEL_TIME_COL    0
#define SEL_TIME_FIL    0




#define OFFSET_XF        7
#define OFFSET_B         15
#define OFFSET_VEL       7

// RUNNING
#define RUN              "Running...      "
#define PAUSE_FINISH     " Pause   Finish "

#define OFFSET_PER       12  // para poner el porcentaje si se desea // SCREEN_H

#endif // SCREEN_H