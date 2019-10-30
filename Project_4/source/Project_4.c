
/**
 * @file    Project_4.c
 * @brief   Application entry point.
 */

#include "Project_4.h"

LoggerHandle logger;
RGBLEDHandle led;
I2CHandle i2c;
TMP102Handle tmp;

int main(void) {


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    PRINTF("\n\r");

	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, false);

	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LOGGERObject));
	Logger_enable(logger);

	i2c = I2C_init((void*)I2C_0_BASE_ADDRESS, sizeof(I2C_OBJ));

	tmp = malloc(sizeof(TMP102_OBJ));
	tmp = TMP102_Constructor((void *)tmp, sizeof(RGBLEDObject), i2c, 0x48);


	TMP102_wakeup(tmp);

	float temperature = TMP102_readTemp(tmp);

	PRINTF("Temperature:%f\n\r",temperature);












}
