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

/**
* @brief Control function for the TBSM
*
* @param currentState		the CSM Pointer
* @param tmp		temp sensor handle
* @param logger		logger handle
* @param led		led handle
*
* @return table entry for next state
*/
struct tableEntry* doCurrentState(struct tableEntry* currentState, TMP102Handle tmp, LoggerHandle logger, RGBLEDHandle led);


#endif /* STATEMACHINE_TABLEDRIVENSTATEMACHINE_H_ */
