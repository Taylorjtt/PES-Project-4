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

CSMHandle CSM_Contstructor(void * pmemory, const size_t numBytes, LoggerHandle logger, RGBLEDHandle led);
STATE CSM_doControl(CSMHandle handle,TMP102Handle tmp);

#endif /* STATEMACHINE_CLASSICSTATEMACHINE_H_ */
