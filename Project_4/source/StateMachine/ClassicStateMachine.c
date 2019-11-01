/*
 * ClassicStateMachine.c
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */


#include "ClassicStateMachine.h"


CSMHandle CSM_Contstructor(void * pmemory, const size_t numBytes, LoggerHandle logger)
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
	return handle;
}
STATE CSM_doControl(CSMHandle handle,TMP102Handle tmp)
{
	CSM_OBJ *obj = (CSM_OBJ *)handle;

	switch(obj->currentState)
	{
		case READ_TEMP:
		{
			Logger_logString(obj->logger, "Entered READ_TEMP state", "CSM_doControl", DEBUG_LEVEL);
			delayMilliseconds(1000);
			obj->currentState = WAIT;
			break;
		}
		case WAIT:
		{
			Logger_logString(obj->logger, "Entered WAIT state", "CSM_doControl", DEBUG_LEVEL);
			delayMilliseconds(1000);
			obj->currentState = ALERT;
			break;
		}
		case ALERT:
		{
			Logger_logString(obj->logger, "Entered ALERT state", "CSM_doControl", DEBUG_LEVEL);
			delayMilliseconds(1000);
			obj->currentState = DISCONNECTED;
			break;
		}
		case DISCONNECTED:
		{
			Logger_logString(obj->logger, "Entered DISCONNECTED state", "CSM_doControl", DEBUG_LEVEL);
			delayMilliseconds(1000);
			obj->currentState = READ_TEMP;
			break;
		}
	}
}
