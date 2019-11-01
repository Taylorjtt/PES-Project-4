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
 * @file TMP102.c
 * @brief
 *
 *  @author John Taylor
 * 	@date Oct 29, 2019
 *
 */
#include "TMP102.h"
//https://www.sparkfun.com/products/13314
TMP102Handle TMP102_Constructor(void * pmemory, const size_t numBytes,I2CHandle i2cHandle, uint16_t address)
{
	TMP102Handle handle;
	if(numBytes < sizeof(TMP102_OBJ))
	{
		return((TMP102Handle)NULL);
	}
	handle = (TMP102Handle)pmemory;
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	tmp->i2cHandle = i2cHandle;
	tmp->address = address;

	return handle;

}
void TMP102_openPointerRegister(TMP102Handle handle,uint8_t pointerRegister)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	I2C_command(tmp->i2cHandle,tmp->address, pointerRegister);
}
void TMP102_readRegister(TMP102Handle handle,uint8_t registerAddress,uint8_t * buffer)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	I2C_ReadRegisters(tmp->i2cHandle, tmp->address, registerAddress, 2, buffer);
}
float TMP102_readTemp(TMP102Handle handle)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	int16_t temp;
	uint8_t buffer[2];
	TMP102_readRegister(handle, TEMPERATURE_REGISTER, buffer);

	if(buffer[1]&0x01)
	{
		//13 bit mode
		// Combine bytes to create a signed int
		temp = ((buffer[0]) << 5) | (buffer[1] >> 3);
		// Temperature data can be + or -, if it should be negative,
		// convert 13 bit to 16 bit and use the 2s compliment.
		if(temp > 0xFFF)
		{
			temp |= 0xE000;
		}

	}
	else
	{
		//12 bit mode
		// Combine bytes to create a signed int
		temp = ((buffer[0]) << 4) | (buffer[1] >> 4);
		// Temperature data can be + or -, if it should be negative,
		// convert 12 bit to 16 bit and use the 2s compliment.
		if(temp > 0x7FF)
		{
			temp |= 0xF000;
		}
	}
	return temp * 0.0625;

}
void TMP102_sleep(TMP102Handle handle)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t buffer[2];
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);

	buffer[0] |= 0x01;

	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);
}
void TMP102_wakeup(TMP102Handle handle)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t buffer[2];
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);

	buffer[0] &= 0xFE;

	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);

}
bool TMP102_alert(TMP102Handle handle)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t buffer[2];
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);

	buffer[1] &= 0x20;
	return buffer[1]>>5;

}
void TMP102_setThreshold(TMP102Handle handle, THRESHOLD_T thresholdType, float temperature)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t buffer[2];
	if(temperature > 150.0f)
	{
		temperature = 150.0f;
	}
	if(temperature < -55.0)
	{
		temperature = -55.0f;
	}


	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);

	bool ext = (buffer[1] & 0x10) >> 4;

	temperature = temperature/0.0625;

	if(ext)
	{
		//13 bit mode
		buffer[0] = (uint8_t)(((int32_t)temperature)>>5);
		buffer[1] = (uint8_t)(((int32_t)temperature)<<3);
	}
	else
	{
		//12 bit mode
		buffer[0] = (uint8_t)(((int32_t)temperature)>>4);
		buffer[1] = (uint8_t)(((int32_t)temperature)<<4);
	}

	if(thresholdType == LOW_THRESHOLD)
	{
		I2C_writeBytes(tmp->i2cHandle, tmp->address, T_LOW_REGISTER, buffer, 2);
	}
	else if (thresholdType == HIGH_THRESHOLD)
	{
		I2C_writeBytes(tmp->i2cHandle, tmp->address, T_HIGH_REGISTER, buffer, 2);
	}

}

float TMP102_readTempThreshold(TMP102Handle handle, THRESHOLD_T thresholdType)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t buffer[2];
	int16_t temp;

	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	bool ext = (buffer[1] & 0x10) >> 4;

	if(thresholdType == LOW_THRESHOLD)
	{
		TMP102_readRegister(tmp, T_LOW_REGISTER, buffer);
	}
	else if (thresholdType == HIGH_THRESHOLD)
	{
		TMP102_readRegister(tmp, T_HIGH_REGISTER, buffer);
	}

	if(ext)
	{
		temp = ((buffer[0]) << 5) | (buffer[1] >> 3);
		if(temp > 0xFFF)
		{
			(temp)|= 0xE000;
		}
	}
	else
	{
		temp = ((buffer[0]) << 4) | (buffer[1] >> 4);
	    if(temp > 0x7FF)
		{
	    	(temp) |= 0xF000;
	    }
	}

	return temp*0.0625f;

}
void TMP102_setConversionRate(TMP102Handle handle,CONVERSION_RATE conversionRate)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t rate = conversionRate & 0x3;
	uint8_t buffer[2] = {0x00,0x00};
	TMP102_readRegister(handle, CONFIG_REGISTER, buffer);
	buffer[1] &= 0x3F;
	buffer[1] |= rate<<6;
	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);

}
void TMP102_setExtendedMode(TMP102Handle handle, EXTENDED_MODE extendedMode)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t mode = extendedMode;
	uint8_t buffer[2] = {0x00,0x00};
	TMP102_readRegister(handle, CONFIG_REGISTER, buffer);
	buffer[1] &= 0xEF;
	buffer[1] |= mode<<4;
	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);


}
void TMP102_setAlertPolarity(TMP102Handle handle,ALERT_POLARITY alertPolarity)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t alert = alertPolarity;
	uint8_t buffer[2] = {0x00,0x00};
	TMP102_readRegister(handle, CONFIG_REGISTER, buffer);
	buffer[0] &= 0xFB;
	buffer[0] |= alert<<2;
	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);

}
void TMP102_setFaultNumber(TMP102Handle handle,NUMBER_OF_FAULTS numberOfFaults)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t fault = numberOfFaults & 0x3;
	uint8_t buffer[2] = {0x00,0x00};
	TMP102_readRegister(handle, CONFIG_REGISTER, buffer);
	buffer[0] &= 0xE7;
	buffer[0] |= fault<<3;
	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);


}
void TMP102_setAlertMode(TMP102Handle handle,ALERT_MODE alertMode)
{
	TMP102_OBJ *tmp = (TMP102_OBJ *)handle;
	uint8_t mode = alertMode;
	uint8_t buffer[2] = {0x00,0x00};
	TMP102_readRegister(handle, CONFIG_REGISTER, buffer);
	buffer[0] &= 0xFD;
	buffer[0] |= mode<<1;
	I2C_writeBytes(tmp->i2cHandle, tmp->address, CONFIG_REGISTER, buffer, 2);

}
