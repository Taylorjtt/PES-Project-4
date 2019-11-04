/*
 * ClassicStateMachine.h
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */

#ifndef STATEMACHINE_CLASSICSTATEMACHINE_H_
#define STATEMACHINE_CLASSICSTATEMACHINE_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <util.h>
#include <TMP102/TMP102.h>
#include <Logger/logger.h>
#include "LED/RGB.h"
#include "MKL25Z4.h"
#define DELAY 15000
extern bool alarm;
typedef enum {READ_TEMP,WAIT,ALERT,DISCONNECTED, DONE}STATE;
typedef struct _CSM_OBJ_
{
	STATE currentState;
	LoggerHandle logger;
	uint16_t averageCount;
	float total;
	float average;
	float currentTemp;
	uint8_t timoutCount;
	RGBLEDHandle led;

}CSM_OBJ;
typedef struct _CSM_OBJ_ *CSMHandle;

/**
* @brief Constructor for Classic State Machine Object
*
* Given a chunk of memory, the size of an CSM_OBJ object and the necessary modules return a pointer to the object
*
* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
*
* @param logger		logger to be used with the object
* @param led  		led to be used with the project
*
*
* @return CSMHandle a pointer to an _CSM_OBJ_
*/
CSMHandle CSM_Contstructor(void * pmemory, const size_t numBytes, LoggerHandle logger, RGBLEDHandle led);
/**
* @brief Control function for the CSM
*
* @param handle		the CSM Pointer
* @param tmp		temp sensor handle
*
* @return STATE indicating if the statemachine is done
*/
STATE CSM_doControl(CSMHandle handle,TMP102Handle tmp);

#endif /* STATEMACHINE_CLASSICSTATEMACHINE_H_ */
