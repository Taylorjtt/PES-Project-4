/*
 * TableDrivenStateMachine.h
 *
 *  Created on: Nov 4, 2019
 *      Author: john
 */

#ifndef STATEMACHINE_TABLEDRIVENSTATEMACHINE_H_
#define STATEMACHINE_TABLEDRIVENSTATEMACHINE_H_

#include "ClassicStateMachine.h"



struct tableEntry
{
	STATE 		  currentState;
	STATE         complete;
	STATE         alert;
	STATE         timeout;
	STATE         disconnect;
};
extern struct tableEntry stateTable[];

struct tableEntry* doCurrentState(struct tableEntry* currentState, TMP102Handle tmp, LoggerHandle logger, RGBLEDHandle led);


#endif /* STATEMACHINE_TABLEDRIVENSTATEMACHINE_H_ */
