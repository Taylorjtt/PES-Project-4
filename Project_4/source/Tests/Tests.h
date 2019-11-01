/*
 * Tests.h
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */

#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_
#include "../uCUnit/uCUnit.h"
#include "Project_4.h"
#define RED_BASE GPIOB
#define RED_PIN 18U

#define GREEN_BASE GPIOB
#define GREEN_PIN 19U

#define BLUE_BASE GPIOD
#define BLUE_PIN 1U

void testTMP(void);

#endif /* TESTS_TESTS_H_ */
