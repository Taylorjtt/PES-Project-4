*John Taylor*
# PES-Project-4 I2C Temperature Sensing
## Introduction
This repository includes an I2C driver and a driver for the TMP102 temperature sensor from Texas Instruments. Control is provided by both a classic switch based state machine as well as an obscure table based state machine. Logger code has been provided that outputs status, debug and test messages to UART. A test suite has also been provided that tests the TMP102 driver. The code has been tested Using MCUXPresso on the **FRDM-KL25Z** dev board.
## Observations

### I2C
I always forget that when addressing an I2C device you need to shift the slave address and add the r/w bit at the end. Every time I have ever implemented an I2C driver I get hung up on this for at least an hour.


## Build Notes
1. Pull the repo from github
2. Import it into MCUXpresso IDE
3. You should be able to run the project easily since we aren't doing any weird cross compilation
### Modes
To run normal mode the top of Project_4.c should look like
~~~
//#define TEST
//#define DB
~~~
To run Debug  mode the top of Project_4.c should look like
~~~
//#define TEST
#define DB
~~~
To run the test suite  the top of Project_4.c should look like
~~~
#define TEST
//#define DB
~~~
