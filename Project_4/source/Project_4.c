
/**
 * @file    Project_4.c
 * @brief   Application entry point.
 */
#define FREEDOM
#include "Project_4.h"

LoggerHandle logger;
RGBLEDHandle led;

int main(void) {


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();


}
