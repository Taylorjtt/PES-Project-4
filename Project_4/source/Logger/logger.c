/*****************************************************************************
* Copyright (C) 2019 by John Taylor
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. John Taylor and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/
/*
 * @file logger.c
 * @brief Cross platform Logger
 *
 *  @author John Taylor
 * 	@date Aug 11, 2019
 *
 */
#include "logger.h"
LoggerHandle Logger_Constructor(void *pmemory, const size_t numbytes)
{
	LoggerHandle handle;
	LOGGERObject *obj;

	if(numbytes < sizeof(LOGGERObject))
	{
		return ((LoggerHandle)NULL);

	}

	handle = (LoggerHandle)pmemory;
	obj = (LOGGERObject *)handle;
	obj->status = DISABLED;
	return handle;
}
void Logger_enable(LoggerHandle handle)
{
	LOGGERObject *obj = (LOGGERObject *)handle;
	obj->status = ENABLED;
}
void Logger_disable(LoggerHandle handle)
{
	LOGGERObject *obj = (LOGGERObject *)handle;
	obj->status = DISABLED;
}
LOGGER_STATUS Logger_status(LoggerHandle handle)
{
	LOGGERObject *obj = (LOGGERObject *)handle;
	return obj->status;
}
void Logger_logData(LoggerHandle handle, uint8_t* loc, size_t length)
{
	LOGGERObject *obj = (LOGGERObject *)handle;
	if(obj->status == ENABLED)
	{
		for(int i = 0; i < length; i++)
		{
			uintptr_t address = (uintptr_t)(loc + i);
			#ifdef FREEDOM
			PRINTF("LOGGER: Address: %02X\tData:%X\n\r",address,loc[i]);
			#else
			printf("LOGGER: Address: %02X\tData:%X\n\r",(uint32_t)address,loc[i]);
			#endif
		}
		#ifdef FREEDOM
			PRINTF("\n\r");
		#else
			printf("\n\r");
		#endif
	}
}
void Logger_logString(LoggerHandle handle, const char * string)
{
	LOGGERObject *obj = (LOGGERObject *)handle;
	if(obj->status == ENABLED)
	{
		printf("LOGGER: %s\n\r",string);
	}
}
void Logger_logInt(LoggerHandle handle, uint8_t num)
{
	LOGGERObject *obj = (LOGGERObject *)handle;
	if(obj->status == ENABLED)
	{
		printf("LOGGER: %d\n\r",num);
	}
}
