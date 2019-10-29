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
 * @file Project_3.h
 * @brief
 *
 *  @author John Taylor
 * 	@date Oct 14, 2019
 *
 */
#ifndef PROJECT_4_H_
#define PROJECT_4_H_
#define FREEDOM
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "LED/RGB.h"
#include "Logger/logger.h"
#include "I2C/I2C.h"
#include "TMP102/TMP102.h"

#define RED_BASE GPIOB
#define RED_PIN 18U

#define GREEN_BASE GPIOB
#define GREEN_PIN 19U

#define BLUE_BASE GPIOD
#define BLUE_PIN 1U
extern LoggerHandle logger;
extern RGBLEDHandle led;

#endif /* PROJECT_4_H_ */
