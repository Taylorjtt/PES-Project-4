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
#include "CMSIS/MKL25Z4.h"
#define I2C_0_BASE_ADDRESS (0x40066000u)
#define I2C_1_BASE_ADDRESS (0x40067000u)
///https://github.com/sunsided/frdm-kl25z-marg-fusion/blob/master/frdm-kl25z-acc-uart/Project_Headers/i2c/i2c.h
//https://github.com/sunsided/frdm-kl25z-marg-fusion/blob/master/frdm-kl25z-acc-uart/Sources/i2c/i2c.c
__STATIC_INLINE void I2C_WaitWhileBusy()
{
	while((I2C0->S & I2C_S_BUSY_MASK)!=0) {}
}
#define I2C_WRITE_ADDRESS(slaveAddress) 	((uint8_t)((slaveAddress << 1) | 0))
#define I2C_READ_ADDRESS(slaveAddress) 	((uint8_t)((slaveAddress << 1) | 1))
#define I2C_ENABLE_BIT 1 << 7
#define I2C_IR_ENABLE_BIT 1 << 6
#define I2C_MODE_BIT 1 << 5
#define I2C_TRANSMIT_MODE_BIT 1 << 4
#define I2C_TRANS_ACK_ENABLE_BIT 1 << 3
#define I2C_RSTART_BIT 1 << 2
#define I2C_WAKEUP_EN_BIT 1 << 1
#define I2C_DMA_EN_BIT 1 << 0
#define I2C_WAIT while((I2C0->S & I2C_S_IICIF_MASK) == 0){} \
		I2C0->S |= I2C_S_IICIF_MASK;


#define I2C_DRIVE_BIT 1 << 5


#define FREQUENCY_ICR(x)  (x) & (0x3F)
#define FREQUENCY_MULT(x)  (x << 6) & (0xC0)

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
I2CHandle I2C_init(void *pmemory, const size_t numBytes);
void I2C_command(I2CHandle handle, uint8_t address,uint8_t data);
void I2C_writeByte(I2CHandle handle, uint8_t address,uint8_t reg,uint8_t data);
void I2C_writeBytes(I2CHandle handle, uint8_t address,uint8_t reg,uint8_t* data, size_t length);
void I2C_start(I2CHandle handle, uint8_t address);
void I2C_stop(I2CHandle handle);
void I2C_write(I2CHandle handle,uint8_t data);
void I2C_ReadRegisters(I2CHandle handle, uint8_t address,uint8_t startRegisterAddress, uint8_t registerCount, uint8_t*  buffer);
uint8_t I2C_readRegister(I2CHandle handle, uint8_t address, uint8_t registerAddress);
void I2C_sendRepeatedStart(I2CHandle handle);
void I2C_EnterReceiveModeWithoutAck(I2CHandle handle);
uint8_t I2C_driveClock(I2CHandle handle);
void I2C_DisableAck(I2CHandle handle);
void I2C_EnterReceiveModeWithAck(I2CHandle handle);

#endif /* I2C_I2C_H_ */
