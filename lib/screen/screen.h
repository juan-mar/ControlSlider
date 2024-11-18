
#ifndef SCREEN_H
#define SCREEN_H

// Define screen positions for cursor placement
enum cursor_col{COL0 = 0, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14, COL15};
enum cursor_fil{FILA0 = 0, FILA1};

// Define positions for menu items
#define SEL_DIS_COL     0
#define SEL_DIS_FIL     0
#define LEFT_COL        2
#define LEFT_FIL        2
#define RIGHT_COL       3
#define RIGHT_FIL       3
#define OK_COL          4
#define OK_FIL          4


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
#define PARTS            " Set Parts     B"
#define ADD_DEL          "Cant:   Add  Del"
#define EDIT_PARTS_COL  0
#define EDIT_PARTS_FIL  0
#define ADD_PART_COL    7
#define ADD_PART_FIL    1
#define DEL_COL         12
#define DEL_FIL         1
#define CANT_PART_COL   5
#define CANT_PART_FIL   1


// SET PARTS
#define TIME_BACK        " Times         B"
#define POSITIONS        " Distancies     "
#define TIME_BK_COL     0
#define TIME_BK_FIL     0
#define DISTANCES_COL   0
#define DISTANCES_FIL   1

//EDIT DISTANCES
#define DISTANCES_n       " X :     cm     "
#define DIS_COL          0
#define DIS_FIL          0

//EDIT TIMES
#define TIME_SELECT_0     " Time :     s   "
#define TIME_COL          0
#define TIME_FIL          0


// RUNNING
#define RUN              " ReStart        "
#define PAUSE_FINISH     " Pause   Finish "
#define RESUME_FINISH    " Resume  Finish "
#define RESTART_COL      0  
#define RESTART_FIL      0
#define PAUSE_COL       0
#define PAUSE_FIL       1
#define FINISH_COL      8
#define FINISH_FIL      1

#endif // SCREEN_H