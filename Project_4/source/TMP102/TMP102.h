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

typedef struct _TMP102_OBJ_
{
	volatile I2CHandle i2cHandle;
	uint16_t address;
	LoggerHandle logger;

}TMP102_OBJ;

typedef enum { QUARTER_HZ,ONE_HZ, FOUR_HZ, EIGHT_HZ}CONVERSION_RATE;
typedef enum {EXTENDED_MODE_DISABLED,EXTENDED_MODE_ENABLED}EXTENDED_MODE;
typedef enum {ACTIVE_LOW,ACTIVE_HIGH}ALERT_POLARITY;
typedef enum {ONE_FAULT,TWO_FAULTS,FOUR_FAULTS,SIX_FAULTS}NUMBER_OF_FAULTS;
typedef enum {COMPARATOR_MODE,THERMOSTAT_MODE}ALERT_MODE;
typedef enum {LOW_THRESHOLD,HIGH_THRESHOLD}THRESHOLD_T;

#define TEMPERATURE_REGISTER 0x00
#define CONFIG_REGISTER 0x01
#define T_LOW_REGISTER 0x02
#define T_HIGH_REGISTER 0x03

typedef struct _TMP102_OBJ_ *TMP102Handle;
TMP102Handle TMP102_Constructor(void * pmemory, const size_t numBytes,I2CHandle i2cHandle, uint16_t address, LoggerHandle logger);
float TMP102_readTemp(TMP102Handle handle);
void TMP102_sleep(TMP102Handle handle);
void TMP102_wakeup(TMP102Handle handle);
bool TMP102_alert(TMP102Handle handle);
void TMP102_setThreshold(TMP102Handle handle,THRESHOLD_T thresholdType, float temperature);
float TMP102_readTempThreshold(TMP102Handle handle, THRESHOLD_T thresholdType);
void TMP102_setConversionRate(TMP102Handle handle,CONVERSION_RATE conversionRate);
void TMP102_setExtendedMode(TMP102Handle handle, EXTENDED_MODE extendedMode);
void TMP102_setAlertPolarity(TMP102Handle handle,ALERT_POLARITY alertPolarity);
void TMP102_setFaultNumber(TMP102Handle handle,NUMBER_OF_FAULTS numberOfFaults);
void TMP102_setAlertMode(TMP102Handle handle,ALERT_MODE alertMode);

void TMP102_openPointerRegister(TMP102Handle handle,uint8_t pointerRegister);
bool TMP102_readRegister(TMP102Handle handle,uint8_t registerAddress,uint8_t * buffer);
bool TMP102_isConnected(TMP102Handle handle);

#endif /* TMP102_TMP102_H_ */
