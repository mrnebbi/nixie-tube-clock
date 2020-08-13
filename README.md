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
* 2 x 22pF Capacitors _(for ATmega)_
* 1 x 16MHz Crystal _(for ATmega)_
* 2 x Momentary switches _(for set and increment controls)_
* 1 x DC barrel jack _(for power to HV supply and 12V stepdown circuit)_
* 6 x 10k resistors _(for switches and IN-14s)_
* 1 x 100k resistor _(for IN-3)_
* 1 x 22k resistor _(for IN-3)_
* 1 x Stepdown switch regulator,LM2575T-5 2.2A _(for 12V to 5V stepdown circuit)_
* 1 x Schottky barrier diode,1N58191A 40V _(for 12V to 5V stepdown circuit)_
* 1 x Inductor radial ELC08D 330uH _(for 12V to 5V stepdown circuit)_
* 1 x Al Electrolytic Cap 105C 16V 330uF _(for 12V to 5V stepdown circuit)_
* 1 x M radial Al elect cap,100uF 16V 85deg C _(for 12V to 5V stepdown circuit)_

## Todo

- Update Eagle files with 12V to 5V circuit
- Add pinout
