*John Taylor*
# PES-Project-4 I2C Temperature Sensing
## Introduction
This repository includes an I2C driver and a driver for the TMP102 temperature sensor from Texas Instruments. Control is provided by both a classic switch based state machine as well as an obscure table based state machine. Logger code has been provided that outputs status, debug and test messages to UART. A test suite has also been provided that tests the TMP102 driver. The code has been tested Using MCUXPresso on the **FRDM-KL25Z** dev board.

## Note on how my "Alert" state works
In my version of the code, if an alert is triggered in the "temp read" state it will enter the alert state and stay there until the temperature rises above 0 degrees C. This made more sense from a practical perspective to me. I could have implemented it the other way, and I actually did at first if you look back at the commits, but it just didn't seem right to me so I tried to improve it.

## Observations

### I2C
I always forget that when addressing an I2C device you need to shift the slave address and add the r/w bit at the end. Every time I have ever implemented an I2C driver I get hung up on this for at least an hour.


## Build Notes
1. Pull the repo from github
2. Import it into MCUXpresso IDE
3. You should be able to run the project easily since we aren't doing any weird cross compilation
### Modes
To run normal mode the top of  mode.h should look like
~~~
//#define TEST
//#define DB
~~~
To run Debug  mode the top of mode.h should look like
~~~
//#define TEST
#define DB
~~~
To run the test suite  the top of  mode.h should look like
~~~
#define TEST
//#define DB
~~~

## References
I pattern matched the following references for my I2C code
~~~
https://github.com/sunsided/frdm-kl25z-marg-fusion/blob/master/frdm-kl25z-acc-uart/Project_Headers/i2c/i2c.h
https://github.com/sunsided/frdm-kl25z-marg-fusion/blob/master/frdm-kl25z-acc-uart/Sources/i2c/i2c.c
~~~
I pattern matched the following references for my tmp code
~~~
https://github.com/sparkfun/Digital_Temperature_Sensor_Breakout_-_TMP102/tree/V_H13.0/Libraries/Arduino/SparkFun_TMP102_Arduino_Library/src
~~~
