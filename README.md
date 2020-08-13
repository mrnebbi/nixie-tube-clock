# Nixie Tube Clock #


## Overview ##

My Nixie Tube clock is driven by a ATMega328P _(the same MCU used in an Arduino Uno)_, four IN-14 Nixie Tubes, an IN-3 neon lamp, and a DS3231 RTC clock module. The tubes are powered by a high power [DC supply](https://www.electroresales.com/hv-psu.html).

## Schematics

[Main board](https://github.com/mrnebbi/nixie-tube-clock/raw/master/Eagle/Nixie%20schematic.pdf) - The main circuit board layout is mostly included in the Eagle schematic, but a few additions need to be added to the files.
[HV supply](https://github.com/mrnebbi/nixie-tube-clock/raw/master/docs/hv-supply.pdf) - The clock uses an off the shelf high voltage board to step the 12V up to the ~170V needed for the nixie tubes.

## Parts ##

I'm using the following parts in my project:

* 1 x Atmel ATmega328P
* 1 x High Voltage Power Supply [https://www.electroresales.com/hv-psu.html](https://www.electroresales.com/hv-psu.html)
* 1 x DS3231 Real Time Clock Module [eBay](https://www.ebay.co.uk/sch/i.html?_from=R40&_trksid=m570.l1313&_nkw=ds3231&_sacat=0)
* 4 x 74141 (К155ИД1) Nixie Drivers
* 2 x 74HC595N Shift Registers
* 2 x 22pF Capacitors
* 1 x 16MHz Crystal

## Todo

- Update Eagle files with 12V to 5V circuit
- Add pinout
