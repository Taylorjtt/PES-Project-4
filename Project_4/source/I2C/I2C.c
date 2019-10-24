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
 * @file I2C.c
 * @brief
 *
 *  @author John Taylor
 * 	@date Oct 23, 2019
 *
 */
#include "I2C.h"

I2CHandle I2C_init(void *pmemory, const size_t numBytes)
{
	I2CHandle i2cHandle;


	if(numBytes < sizeof(I2C_OBJ))
	{
		return((I2CHandle)NULL);
	}

	// assign the handle
	i2cHandle = (I2CHandle)pmemory;

	I2C_OBJ *i2c = (I2C_OBJ *)i2cHandle;

	//divide by 56 for ~400khz
	i2c->FREQUENCY |= ((FREQUENCY_ICR(0x11)) | (FREQUENCY_MULT(0x0)));

	//enable the peripheral
	i2c->CONTROL_1 |= I2C_ENABLE_BIT;

	return(i2cHandle);
}
void I2C_start(I2CHandle handle, uint8_t address)
{

	I2C_OBJ *i2c = (I2C_OBJ *)handle;
	I2C_WaitWhileBusy();
	//set to transmit
	i2c->CONTROL_1 |= I2C_C1_TX_MASK;
	//send start condition
	//set to master mode
	i2c->CONTROL_1 |= I2C_C1_MST_MASK;
	//send address
	i2c->DATA = I2C_WRITE_ADDRESS(address);
	//wait for ack
	I2C_WAIT
}
void I2C_stop(I2CHandle handle)
{
	I2C_OBJ *i2c = (I2C_OBJ *)handle;
	i2c->CONTROL_1 &= ~((1 << I2C_C1_MST_SHIFT) & I2C_C1_MST_MASK)
					& ~((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);
}
void I2C_write(I2CHandle handle, uint8_t data)
{
	I2C_OBJ *i2c = (I2C_OBJ *)handle;
	//send data
	i2c->DATA = data;
	//wait
	I2C_WAIT
}
void I2C_command(I2CHandle handle, uint8_t address,uint8_t data)
{
	I2C_OBJ *i2c = (I2C_OBJ *)handle;
	I2C_start(handle, address);
	//send data
	i2c->DATA = data;
	//wait
	I2C_WAIT
	//stop
	I2C_stop(handle);
}
void I2C_writeByte(I2CHandle handle, uint8_t address,uint8_t reg,uint8_t data)
{
	I2C_OBJ *i2c = (I2C_OBJ *)handle;

	I2C_start(handle, address);

	//send register addresss
	i2c->DATA = reg;
	//wait
	I2C_WAIT
	//send data
	i2c->DATA = data;
	//wait
	I2C_WAIT

	//stop
	I2C_stop(handle);
}

void I2C_writeBytes(I2CHandle handle, uint8_t address,uint8_t reg,uint8_t* data, size_t length)
{
	I2C_OBJ *i2c = (I2C_OBJ *)handle;
	I2C_start(handle, address);

	//send register addresss
	i2c->DATA = reg;
	//wait
	I2C_WAIT
	//send data
	for(int i = 0; i < length; i++)
	{
		i2c->DATA = data[i];
		//wait
		I2C_WAIT

	}

	//stop
	I2C_stop(handle);
}


