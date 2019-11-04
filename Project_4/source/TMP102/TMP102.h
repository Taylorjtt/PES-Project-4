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
 * @file TMP102.h
 * @brief
 *
 *  @author John Taylor
 * 	@date Oct 29, 2019
 *
 */
#ifndef TMP102_TMP102_H_
#define TMP102_TMP102_H_
#include <stdbool.h>
#include "../I2C/I2C.h"
#include "../Logger/logger.h"
#include "mode.h"
typedef enum { QUARTER_HZ,ONE_HZ, FOUR_HZ, EIGHT_HZ}CONVERSION_RATE;
typedef enum {EXTENDED_MODE_DISABLED,EXTENDED_MODE_ENABLED}EXTENDED_MODE;
typedef enum {ACTIVE_LOW,ACTIVE_HIGH}ALERT_POLARITY;
typedef enum {ONE_FAULT,TWO_FAULTS,FOUR_FAULTS,SIX_FAULTS}NUMBER_OF_FAULTS;
typedef enum {COMPARATOR_MODE,THERMOSTAT_MODE}ALERT_MODE;
typedef enum {LOW_THRESHOLD,HIGH_THRESHOLD}THRESHOLD_T;


typedef struct _TMP102_OBJ_
{
	volatile I2CHandle i2cHandle;
	uint16_t address;
	LoggerHandle logger;

}TMP102_OBJ;



#define TEMPERATURE_REGISTER 0x00
#define CONFIG_REGISTER 0x01
#define T_LOW_REGISTER 0x02
#define T_HIGH_REGISTER 0x03

typedef struct _TMP102_OBJ_ *TMP102Handle;

/**
* @brief Constructor for TMP102
*
* Given a chunk of memory, the size of an TMP102 object and the necessary modules return a pointer to the object
*
* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
*
* @param i2cHandle		i2cHandle to be used with the object
* @param address  		i2c address to be used with the object
* @param logger  		led to be used with the project
*
* @return TMP102Handle a pointer to an _CSM_OBJ_
*/
TMP102Handle TMP102_Constructor(void * pmemory, const size_t numBytes,I2CHandle i2cHandle, uint16_t address, LoggerHandle logger);

/**
* @brief read the current temperature
*
* @param handle		the TMP102 Pointer
*
* @return the current temperature
*
*/
float TMP102_readTemp(TMP102Handle handle);
/**
* @brief put the device into sleep mode
*
* @param handle		the TMP102 Pointer
*
*
*/
void TMP102_sleep(TMP102Handle handle);
/**
* @brief wake the device up
*
* @param handle		the TMP102 Pointer
*
*
*/
void TMP102_wakeup(TMP102Handle handle);
/**
* @brief read the current temperature
*
* @param handle		the TMP102 Pointer
*
* @return true if there is an alert
*
*/
bool TMP102_alert(TMP102Handle handle);
/**
* @brief set the low or high temperature threshodd
*
* @param handle				the TMP102 Pointer
* @param thresholdType		High or low threshold
* @param temperature		temp to set the threshold at
*
*
*/
void TMP102_setThreshold(TMP102Handle handle,THRESHOLD_T thresholdType, float temperature);
/**
* @brief read the low or high temperature threshold
*
* @param handle				the TMP102 Pointer
* @param thresholdType		High or low threshold
* @return 					the threshold
*
*/
float TMP102_readTempThreshold(TMP102Handle handle, THRESHOLD_T thresholdType);
/**
* @brief set the low conversion rate
*
* @param handle				the TMP102 Pointer
* @param conversionRate		conversion rate to set
*
*/
void TMP102_setConversionRate(TMP102Handle handle,CONVERSION_RATE conversionRate);
/**
* @brief enable or disable extended mode
*
* @param handle				the TMP102 Pointer
* @param extendedMode		extended mode enabled/disabled
*
*/
void TMP102_setExtendedMode(TMP102Handle handle, EXTENDED_MODE extendedMode);

/**
* @brief set the alert polarity
*
* @param handle				the TMP102 Pointer
* @param alertPolarity		active high/active low alert polarity
*
*/
void TMP102_setAlertPolarity(TMP102Handle handle,ALERT_POLARITY alertPolarity);
/**
* @brief set number of faults before alert trigger
*
* @param handle				the TMP102 Pointer
* @param numberOfFaults		number of faults to tolerate
*
*/
void TMP102_setFaultNumber(TMP102Handle handle,NUMBER_OF_FAULTS numberOfFaults);
/**
* @brief set alert mode
*
* @param handle				the TMP102 Pointer
* @param alertMode			set alert mode to thermostat or comparator
*
*/
void TMP102_setAlertMode(TMP102Handle handle,ALERT_MODE alertMode);
/**
* @brief read a register
*
* @param handle				the TMP102 Pointer
* @param registerAddress	register to read
* @param buffer				buffer to store register contents
*
* @return whether or not the read was sucessful
*/
bool TMP102_readRegister(TMP102Handle handle,uint8_t registerAddress,uint8_t * buffer);
/**
* @brief is the device connected
*
* @param handle				the TMP102 Pointer
*
* @return whether or not the device is connected
*/
bool TMP102_isConnected(TMP102Handle handle);

#endif /* TMP102_TMP102_H_ */
