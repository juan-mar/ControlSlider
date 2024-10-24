#ifndef EVENTGENERATOR_EVENTGENERATOR_H_
#define EVENTGENERATOR_EVENTGENERATOR_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum{
    RIGHT,
    LEFT,
    ENTER,
    INIT_OF_LINE,
    END_OF_LINE,
    RIGHT_LONG = 10,
    LEFT_LONG,
    ENTER_LONG,
    INIT_OF_LINE_LONG,
    END_OF_LINE_LONG,
    NONE = 0xFF
}events_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/




/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void EG_init(void);

events_t EG_getEvent(void);

bool EG_isEmpty(void);

uint8_t EG_numberOfElements(void);


/*******************************************************************************
 ******************************************************************************/
#endif /* EVENTGENERATOR_EVENTGENERATOR_H_ */
