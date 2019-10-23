
/**
 * @file    Project_4.c
 * @brief   Application entry point.
 */

#include "Project_4.h"

LoggerHandle logger;
RGBLEDHandle led;

int main(void) {


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, true);

	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LoggerHandle));



}
