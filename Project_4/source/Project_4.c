
/**
 * @file    Project_4.c
 * @brief   Application entry point.
 */

#include "Project_4.h"

//#define TEST
#define DEBUG
#define TMP102_ADDRESS 0x48
LoggerHandle logger;
RGBLEDHandle led;
I2CHandle i2c;
TMP102Handle tmp;
CSMHandle stateMachine;



int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    /*
     * The board is running at 48MZ therefore 480 ticks equals 10 microsecond
     */
    SysTick_Config(480);
    PRINTF("\n\r");

	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, false);

	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LOGGERObject));
	Logger_enable(logger);

	i2c = I2C_init((void*)I2C_0_BASE_ADDRESS, sizeof(I2C_OBJ));

	tmp = malloc(sizeof(TMP102_OBJ));
	tmp = TMP102_Constructor((void *)tmp, sizeof(TMP102_OBJ), i2c, TMP102_ADDRESS, logger);
	stateMachine = malloc(sizeof(CSM_OBJ));
	stateMachine = CSM_Contstructor((void *)stateMachine, sizeof(CSM_OBJ), logger);

#ifdef TEST
	testTMP();
#else

	if(POST())
	{
		Logger_logString(logger, "POST Passed", "main", STATUS_LEVEL);

		while(true)
		{
			CSM_doControl(stateMachine, tmp);
		}

	}
	else
	{
		Logger_logString(logger, "POST Failed", "main", STATUS_LEVEL);
	}
#endif

}

bool POST(void)
{
	RGBLED_set(led, true, false, false);
	delayMilliseconds(500);
	RGBLED_set(led, false, true, false);
	delayMilliseconds(500);
	RGBLED_set(led, false, false, true);
	delayMilliseconds(500);
	RGBLED_set(led, false, false, false);


	return TMP102_isConnected(tmp);

}



