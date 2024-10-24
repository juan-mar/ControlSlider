#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS 
 ******************************************************************************/
typedef enum{
    ACT_LOW,
    ACT_HIGH
}activeLogic_t;

typedef enum{
    PRESS,
    PRESSED,
    NOT_PRESSED
}state_t;

/*******************************************************************************
 * CLASSES 
 ******************************************************************************/
class Button{
public:
    Button(int pin, activeLogic_t activeLogic = ACT_LOW);
    ~Button();
    state_t getState();
    
private:
    int pin;
    activeLogic_t activeLogic;
    state_t prevState;

};




/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/




/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 ******************************************************************************/
#endif /* BUTTON_BUTTON_H_ */