Table of contents
---------------------------

  * [Overview](#overview)
  * [Software](#software)
  * [Hardware](#hardware)

  
Overview
--------------------
* Name : ATTINY_CHRISTMAS_LIGHTS
* Description: 

Arduino Project , A controller board based on ATtiny85 and a h-bridge to control 
a set of battery operated chasing swapped polarity Christmas LED lights. Can be used to replace the controller board on these very common LED chains if existing manufacturers controller board fails beyond repair.

Software
------------------------

I used this library for Attiny85 sleep mode, it's requires one small mod,
Add  wdt_disable(); to the ISR(WDT_vect) function to prevent unexpected behaviour

1. [tinysnore](https://github.com/connornishijima/TinySnore)

The software on the ATtiny85 executes a series of displays on the LED chain for six hours and then goes to sleep for 18 hours.

Hardware
--------------------------

Specification of LED chain

1. Chasing LED Lights
2. 120 LEDS
3. 60 red + yellow  , 60 Blue + green
4. Both chains wired in swapped polarity
5. LED bulb .03W  3V
6. battery 3-4 AA 4.5-5.5
7. wattage 3.6 W 

![o](https://github.com/gavinlyonsrepo/ATTINY_CHRISTMAS_LIGHTS/blob/main/extras/image/light.png)
