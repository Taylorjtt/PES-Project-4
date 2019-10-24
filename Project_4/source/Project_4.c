
/**
 * @file    Project_4.c
 * @brief   Application entry point.
 */

#include "Project_4.h"

LoggerHandle logger;
RGBLEDHandle led;
I2CHandle i2c;

int main(void) {


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, false);

	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LoggerHandle));
	Logger_enable(logger);

	i2c = I2C_init((void*)I2C_0_BASE_ADDRESS, sizeof(I2C_OBJ));
	I2C_command(i2c, 0x70, 0x21);
	I2C_command(i2c, 0x70, 0x81);
	I2C_command(i2c, 0x70, (0xE0 | 0xF));

	I2C_start(i2c, 0x70);
	I2C_write(i2c, 0x0);

	for(int i = 0; i <8; i++)
	{
		I2C_write(i2c, 0xAA);
		I2C_write(i2c, 0xFF);
	}

	I2C_stop(i2c);










}
