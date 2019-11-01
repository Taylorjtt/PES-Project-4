/*
 * Tests.c
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */
#include "Tests.h"

void printBuffer(uint8_t * buffer)
{
	PRINTF("buffer[0]: 0x%X\n\r",buffer[0]);
	PRINTF("buffer[1]: 0x%X\n\r",buffer[1]);
}
void testTMP(void)
{
	UCUNIT_TestcaseBegin("Testing Setting Config Register");
	uint8_t buffer[2] = {0x00,0x00};

	TMP102_sleep(tmp);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual(buffer[0] & 0x1,1);
	TMP102_wakeup(tmp);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual(buffer[0] & 0x1,0);

	TMP102_setConversionRate(tmp, QUARTER_HZ);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[1]>>6) & 0x3,0);
	TMP102_setConversionRate(tmp, ONE_HZ);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[1]>>6) & 0x3,1);
	TMP102_setConversionRate(tmp, FOUR_HZ);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[1]>>6) & 0x3,2);
	TMP102_setConversionRate(tmp, EIGHT_HZ);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[1]>>6) & 0x3,3);

	TMP102_setExtendedMode(tmp, EXTENDED_MODE_ENABLED);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[1]>>4) & 0x1,1);
	TMP102_setExtendedMode(tmp, EXTENDED_MODE_DISABLED);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[1]>>4) & 0x1,0);

	TMP102_setAlertPolarity(tmp, ACTIVE_LOW);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>2) & 0x1,0);
	TMP102_setAlertPolarity(tmp, ACTIVE_HIGH);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>2) & 0x1,1);

	TMP102_setFaultNumber(tmp, ONE_FAULT);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>3) & 0x3,0);
	TMP102_setFaultNumber(tmp, TWO_FAULTS);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>3) & 0x3,1);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	TMP102_setFaultNumber(tmp, FOUR_FAULTS);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>3) & 0x3,2);
	TMP102_setFaultNumber(tmp, SIX_FAULTS);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>3) & 0x3,3);

	TMP102_setAlertMode(tmp, COMPARATOR_MODE);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>1) & 0x1,0);
	TMP102_setAlertMode(tmp, THERMOSTAT_MODE);
	TMP102_readRegister(tmp, CONFIG_REGISTER, buffer);
	UCUNIT_CheckIsEqual((buffer[0]>>1) & 0x1,1);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing Setting Threshold Temperatures");
	TMP102_setThreshold(tmp, HIGH_THRESHOLD, 100);
	UCUNIT_CheckIsEqual(100,TMP102_readTempThreshold(tmp, HIGH_THRESHOLD));
	TMP102_setThreshold(tmp, HIGH_THRESHOLD, -50);
	UCUNIT_CheckIsEqual(-50,TMP102_readTempThreshold(tmp, HIGH_THRESHOLD));

	TMP102_setThreshold(tmp, LOW_THRESHOLD, 100);
	UCUNIT_CheckIsEqual(100,TMP102_readTempThreshold(tmp, LOW_THRESHOLD));
	TMP102_setThreshold(tmp, LOW_THRESHOLD, -50);
	UCUNIT_CheckIsEqual(-50,TMP102_readTempThreshold(tmp, LOW_THRESHOLD));


	UCUNIT_TestcaseEnd();
}

