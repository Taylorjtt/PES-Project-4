/*
 * TableDrivenStateMachine.c
 *
 *  Created on: Nov 4, 2019
 *      Author: john
 */


#include "TableDrivenStateMachine.h"
uint16_t averageCount = 1;
float total = 0.0f;
float average = 0.0f;
float currentTemp = 0.0f;
uint16_t timoutCount = 0;
struct tableEntry stateTable[] = {
		{READ_TEMP,WAIT,ALERT,DONE,DISCONNECTED}, 	//temp reading state
		{WAIT,DONE,ALERT,READ_TEMP,DISCONNECTED},	//wait/average state
		{ALERT,WAIT,DONE,DONE,DISCONNECTED}, 		//alert state
		{DISCONNECTED,DONE,DONE,DONE,DONE}, 		//DC
		{DONE,DONE,DONE,DONE,DONE}
};
struct tableEntry* doCurrentState(struct tableEntry* currentState, TMP102Handle tmp, LoggerHandle logger, RGBLEDHandle led)
{
	if(currentState->currentState == READ_TEMP)
	{
		EnableIRQ(PORTA_IRQn);
		Logger_logString(logger, "Entered READ_TEMP state", "doCurrentState", STATUS_LEVEL);
		RGBLED_set(led, false, true, false);
		if(alarm)
		{
			alarm = false;
			return &stateTable[currentState->alert];
		}
		else if(TMP102_isConnected(tmp))
		{
			currentTemp = TMP102_readTemp(tmp);
			return &stateTable[currentState->complete];
		}
		else
		{
			return &stateTable[currentState->disconnect];
		}
	}
	else if(currentState->currentState == WAIT)
	{
		DisableIRQ(PORTA_IRQn);
		RGBLED_set(led, false, true, false);
		Logger_logString(logger, "Entered WAIT state", "doCurrentState", STATUS_LEVEL);

		if(TMP102_isConnected(tmp))
		{
			total += currentTemp;
			average = total/averageCount;
			averageCount++;

			Logger_logTemps(logger, currentTemp,average, "doCurrentState", STATUS_LEVEL);
			delayMilliseconds(DELAY);

			if(averageCount == 4)
			{
				average = 0;
				averageCount = 1;
				total = 0.0f;
				return &stateTable[DONE];
			}

			return &stateTable[currentState->timeout];
		}
		else
		{
			return &stateTable[currentState->disconnect];
		}
	}
	else if(currentState->currentState == ALERT)
	{
		DisableIRQ(PORTA_IRQn);
		RGBLED_set(led, false, false, true);
		Logger_logString(logger, "Entered ALERT state", "doCurrentState", STATUS_LEVEL);

		if(TMP102_isConnected(tmp))
		{
			delayMilliseconds(1000);
			currentTemp = TMP102_readTemp(tmp);
			if(currentTemp > 0)
			{
				return &stateTable[currentState->complete];
			}
			else
			{
				return &stateTable[currentState->currentState];
			}

		}
		else
		{
			return &stateTable[currentState->disconnect];
		}

	}
	else if(currentState->currentState == DISCONNECTED)
	{
		RGBLED_set(led, true, false, false);
		Logger_logString(logger, "Entered DISCONNECTED state", "doCurrentState", STATUS_LEVEL);
		exit(0);
	}
	return &stateTable[currentState->currentState];
}


