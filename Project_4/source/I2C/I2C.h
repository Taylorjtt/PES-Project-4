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

#define I2C0_BASE 0x40066000
#define I2C0_BASE 0x40067000

typedef struct _I2C_Obj_
{
	uint8_t ADRESS_1;
	uint8_t FREQUENCY;
	uint8_t CONTROL_1;
	uint8_t STATUS;
	uint8_t DATA;
	uint8_t CONTROL_2;
	uint8_t FILTER;
	uint8_t RANGE_ADDRESS;
	uint8_t SMB;
	uint8_t ADRESS_2;
	uint8_t SLTH;
	uint8_t SLTL;

}I2C_OBJ;


#endif /* I2C_I2C_H_ */
