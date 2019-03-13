/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 ShiftHrs (1, 2, 3, 4); 
ShiftRegister74HC595 ShiftMins (1, 5, 6, 7);

int delayTime = 1000;
int shortDelayTime = 150;
int pinSet = 0;

boolean digits[10][4] = {
  { LOW, LOW, LOW, LOW }, // ZERO
  { HIGH, LOW, LOW, LOW}, // ONE
  { LOW, HIGH, LOW, LOW }, // TWO
  { HIGH, HIGH, LOW, LOW }, // THREE
  { LOW, LOW, HIGH, LOW }, // FOUR
  { HIGH, LOW, HIGH, LOW }, // FIVE
  { LOW, HIGH, HIGH, LOW }, // SIX
  { HIGH, HIGH, HIGH, LOW }, // SEVEN
  { LOW, LOW, LOW, HIGH }, // EIGHT
  { HIGH, LOW, LOW, HIGH } // NINE
};

int pins[2][4] = {
  { 0, 1, 2, 3 },
  { 4, 5, 6, 7 }
};

void setup() { 
}

void loop() {
  CycleDigits();
}



/*
 * SetDigit(position, digit)
 * Position: 0 & 1 = hours. 2 & 3 = minutes
 * Digit: What digit to show? 0 - 9
 */

void SetDigit(int position, int digit){
  if (position == 0 || position == 2) {
    pinSet = 0;
  } else {
    pinSet = 1;
  }

  if (position == 0 || position == 1) {
    for (int x = 0; x < 4; x++) {
      ShiftHrs.set(pins[pinSet][x], digits[digit][x]);
    }
  } else {
    for (int x = 0; x < 4; x++) {
      ShiftMins.set(pins[pinSet][x], digits[digit][x]);
    }
  }

}


/*
 * ClearDigit(position)
 * Clear a digit at a specific position. Shows no digit.
 * Position: 0 & 1 = hours. 2 & 3 = minutes
 */
 
void ClearDigit(int position){
  if (position == 0 || position == 2) {
    pinSet = 0;
  } else {
    pinSet = 1;
  }

  if (position == 0 || position == 1) {
    for (int x = 0; x < 4; x++) {
      ShiftHrs.set(pins[pinSet][x], HIGH);
    }
  } else {
    for (int x = 0; x < 4; x++) {
      ShiftMins.set(pins[pinSet][x], HIGH);
    }
  }
}

/*
 * ClearAll()
 * Clears all digits at once. Shows no digits.
 */

void ClearAll () {
  ClearDigit(1); // hr 1
  ClearDigit(2); // hr 2
  ClearDigit(3); // min 1
  ClearDigit(4); // min 2
}

/*
 * CycleTubes()
 * Runs all digits through all Nixie tubes to prevent cathode poisoning
 */

void CycleTubes() {
  for (int x = 0; x < 10; x++) {
    SetDigit(0,x);
    SetDigit(1,x);
    SetDigit(2,x);
    SetDigit(3,x);
    delay(delayTime);
  }
  ClearAll();
  delay(delayTime);
}

