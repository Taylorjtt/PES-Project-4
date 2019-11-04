/*
 * ClassicStateMachine.c
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */


#include "ClassicStateMachine.h"

bool alarm = false;
CSMHandle CSM_Contstructor(void * pmemory, const size_t numBytes, LoggerHandle logger, RGBLEDHandle led)
{
	CSMHandle handle;
	if(numBytes < sizeof(CSM_OBJ))
	{
		return((CSMHandle)NULL);
	}
	handle = (CSMHandle)pmemory;
	CSM_OBJ *csm = (CSM_OBJ *)handle;
	csm->currentState = READ_TEMP;
	csm->logger = logger;
	csm->averageCount = 1;
	csm->total = 0.0f;
	csm->average = 0.0f;
	csm->currentTemp = 0.0f;
	csm->timoutCount = 0;
	csm->led = led;
	return handle;
}
STATE CSM_doControl(CSMHandle handle,TMP102Handle tmp)
{
	CSM_OBJ *obj = (CSM_OBJ *)handle;

	switch(obj->currentState)
	{
		case READ_TEMP:
		{
			EnableIRQ(PORTA_IRQn);
			RGBLED_set(obj->led, false, true, false);
			if(alarm)
			{
				obj->currentState = ALERT;
				alarm = false;
				break;
			}
			Logger_logString(obj->logger, "Entered READ_TEMP state", "CSM_doControl", STATUS_LEVEL);
			if(TMP102_isConnected(tmp))
			{
				obj->currentTemp = TMP102_readTemp(tmp);
				obj->currentState = WAIT;
			}
			else
			{
				obj->currentState = DISCONNECTED;
			}

			DisableIRQ(PORTA_IRQn);
			break;
		}
		case WAIT:
		{
			RGBLED_set(obj->led, false, true, false);
			if(TMP102_isConnected(tmp))
			{
				Logger_logString(obj->logger, "Entered WAIT state", "CSM_doControl", STATUS_LEVEL);
				obj->total += obj->currentTemp;
				obj->average = obj->total/obj->averageCount;
				obj->averageCount++;

				Logger_logTemps(obj->logger, obj->currentTemp, obj->average, "CSM_doControl", STATUS_LEVEL);
				delayMilliseconds(DELAY);
				obj->currentState = READ_TEMP;
				if(obj->averageCount == 4)
				{
					obj->average = 0;
					obj->averageCount = 1;
					obj->total = 0.0f;
					return DONE;
				}
			}
			else
			{
				obj->currentState = DISCONNECTED;
			}

			break;
		}
		case ALERT:
		{
			DisableIRQ(PORTA_IRQn);
			RGBLED_set(obj->led, false, false, true);
			Logger_logString(obj->logger, "Entered ALERT state", "CSM_doControl", STATUS_LEVEL);

			if(TMP102_isConnected(tmp))
			{
				obj->currentTemp = TMP102_readTemp(tmp);
				if(obj->currentTemp > 0)
				{
					obj->currentState = WAIT;
				}
				else
				{
					obj->currentState = ALERT;
				}

			}
			else
			{
				obj->currentState = DISCONNECTED;
			}
			delayMilliseconds(DELAY);
			break;
		}
		case DISCONNECTED:
		{
			RGBLED_set(obj->led, true, false, false);
			Logger_logString(obj->logger, "Entered DISCONNECTED state", "CSM_doControl", STATUS_LEVEL);
			exit(0);
			break;
		}
		case DONE:
		{
			Logger_logString(obj->logger, "Entered DONE state, Should not be here", "CSM_doControl", STATUS_LEVEL);
		}
	}
}
