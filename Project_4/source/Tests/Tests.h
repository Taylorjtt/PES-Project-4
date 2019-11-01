/*
 * Tests.h
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */

#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_
#include "../uCUnit/uCUnit.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "source/TMP102/TMP102.h"
#include "source/I2C/I2C.h"
#include "source/LED/RGB.h"
#define RED_BASE GPIOB
#define RED_PIN 18U

#define GREEN_BASE GPIOB
#define GREEN_PIN 19U

#define BLUE_BASE GPIOD
#define BLUE_PIN 1U

void init(void);
void testTMP(void);

#endif /* TESTS_TESTS_H_ */
