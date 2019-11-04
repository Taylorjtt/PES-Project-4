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
 * @file I2C.h
 * @I2C peripherial controller for the KL25Z board
 *
 *  @author John Taylor
 * 	@date Oct 23, 2019
 *
 */
#ifndef I2C_I2C_H_
#define I2C_I2C_H_
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "CMSIS/MKL25Z4.h"
#define I2C_0_BASE_ADDRESS (0x40066000u)
#define I2C_1_BASE_ADDRESS (0x40067000u)
///https://github.com/sunsided/frdm-kl25z-marg-fusion/blob/master/frdm-kl25z-acc-uart/Project_Headers/i2c/i2c.h
//https://github.com/sunsided/frdm-kl25z-marg-fusion/blob/master/frdm-kl25z-acc-uart/Sources/i2c/i2c.c


/**
* @brief function to wait while the i2c peripheral is busy
*/
__STATIC_INLINE void I2C_WaitWhileBusy()
{
	uint32_t i = 0;
	while((I2C0->S & I2C_S_BUSY_MASK)!=0)
	{
		i++;
		if(i > 100000)
		{
			break;
		}
	}

}
/**
* @brief macro to convert an i2c address to a write address
*/
#define I2C_WRITE_ADDRESS(slaveAddress) 	((uint8_t)((slaveAddress << 1) | 0))
/**
* @brief macro to convert an i2c address to a read address
*/

#define I2C_READ_ADDRESS(slaveAddress) 	((uint8_t)((slaveAddress << 1) | 1))
#define I2C_ENABLE_BIT 1 << 7
#define FREQUENCY_ICR(x)  (x) & (0x3F)
#define FREQUENCY_MULT(x)  (x << 6) & (0xC0)

/**
* @brief struct representing the i2c peripheral
*/
typedef struct _I2C_Obj_
{
	__IO uint8_t ADRESS_1;
	__IO uint8_t FREQUENCY;
	__IO uint8_t CONTROL_1;
	__IO uint8_t STATUS;
	__IO uint8_t DATA;
	__IO uint8_t CONTROL_2;
	__IO uint8_t FILTER;
	__IO uint8_t RANGE_ADDRESS;
	__IO uint8_t SMB;
	__IO uint8_t ADRESS_2;
	__IO uint8_t SLTH;
	__IO uint8_t SLTL;


}I2C_OBJ;

typedef struct _I2C_Obj_ *I2CHandle;
/**
* @brief Constructor for I2C object
*

* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
*
*
* @return I2CHandle a pointer to an I2C_OBJ
*/
I2CHandle I2C_init(void *pmemory, const size_t numBytes);
/**
* @brief write a certain number of bytes to the i2c object
*

* @param handle		handle of the object
* @param address	address to write to
* @param reg		register to write to
* @param data		array of byte data to write
* @param length		how many bytes to write
*
* @return boolean indicating if write was succesfull
*/
bool I2C_writeBytes(I2CHandle handle, uint8_t address,uint8_t reg,uint8_t* data, size_t length);

/**
* @brief send a start condition
*

* @param handle		handle of the object
* @param address	address to write to
*
*/
void I2C_start(I2CHandle handle, uint8_t address);

/**
* @brief send a stop condition
*

* @param handle		handle of the object
*
*/
void I2C_stop(I2CHandle handle);

/**
* @brief read registers from an i2c device
*

* @param handle						handle of the object
* @param address					address to write to
* @param startRegisterAddress		register to start reading at
* @param registerCount				how many registers to read
* @param buffer						buffer to store read data
*
* @return boolean indicating if write was succesfull
*/
bool I2C_ReadRegisters(I2CHandle handle, uint8_t address,uint8_t startRegisterAddress, uint8_t registerCount, uint8_t*  buffer);
/**
* @brief send a repeated start condition
*
* @param handle		handle of the object
*
*/
void I2C_sendRepeatedStart(I2CHandle handle);

/**
* @brief read data to drive the clock
*
* @param handle		handle of the object
*
*/
uint8_t I2C_driveClock(I2CHandle handle);
/**
* @brief disable ack
*
* @param handle		handle of the object
*
*/
void I2C_DisableAck(I2CHandle handle);
/**
* @brief enable recieve mode with Ack
*
* @param handle		handle of the object
*
*/
void I2C_EnterReceiveModeWithAck(I2CHandle handle);
/**
* @brief wait for the i2c interrupt flag
*
* @param handle		handle of the object
*
*/
bool I2C_wait(I2CHandle handle);

#endif /* I2C_I2C_H_ */
