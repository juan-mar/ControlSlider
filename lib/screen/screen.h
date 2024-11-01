
#ifndef SCREEN_H
#define SCREEN_H

// Define screen positions for cursor placement
enum cursor_col{COL0 = 0, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14, COL15};
enum cursor_fil{FILA0 = 0, FILA1};

// Define positions for menu items
#define RUN_COL         0
#define RUN_FIL         0
#define SETTING_COL     1
#define SETTING_FIL     1
#define PAUSE_COL       0
#define PAUSE_FIL       0
#define FINISH_COL      1
#define FINISH_FIL      1
#define MANUAL_COL      0
#define MANUAL_FIL      0
#define BLUETOOTH_COL   1
#define BLUETOOTH_FIL   1
#define BACK_COL        2
#define BACK_FIL        2
#define EDIT_PARTS_COL  0
#define EDIT_PARTS_FIL  0
#define ADD_PART_COL    1
#define ADD_PART_FIL    1
#define DEL_COL         2
#define DEL_FIL         2
#define SEL_DIS_COL     0
#define SEL_DIS_FIL     0
#define SEL_DELTA_COL   1
#define SEL_DELTA_FIL   1
#define X0_COL          0
#define X0_FIL          0
#define XF_COL          1
#define XF_FIL          1
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

#define OFFSET_SETTINGS  7
#define OFFSET_END       12 

#define BT_ON            " Bluetooth   ON "
#define BT_OFF           " Bluetooth   OFF"
#define SET_MAN          " Set Manually   "
#define MOVE_MAN         " Move Manually  "

// PARTS
#define PARTS            " Edit Part:     "
#define ADD_DEL          " Add         Del"

#define OFFSET_DEL       12

// PART SETTINGS
#define POSITIONS        " Xo:    Xf:    B"
#define TIME_VEL         " T:   s V:   m/s"

#define OFFSET_XF        7
#define OFFSET_B         15
#define OFFSET_VEL       7

// RUNNING
#define RUN              "Running...      "
#define PAUSE_FINISH     " Pause   Finish "

#define OFFSET_PER       12  // para poner el porcentaje si se desea // SCREEN_H

#endif // SCREEN_H