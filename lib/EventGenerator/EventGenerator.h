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
    ENCODER_RIGHT,
    ENCODER_LEFT,
    ENCODER_SWITCH,
    INIT_OF_LINE,
    END_OF_LINE,
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

void EG_addExternEvent(events_t);

bool EG_isEmpty(void);

uint8_t EG_numberOfElements(void);


/*******************************************************************************
 ******************************************************************************/
#endif /* EVENTGENERATOR_EVENTGENERATOR_H_ */
