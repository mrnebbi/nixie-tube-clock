/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (1, 2, 3, 4); 
int delayTime = 1000;

void setup() { 
}

void loop() {
  TurnOnR9();
  TurnOnL9();
  delay(delayTime);
  TurnOffL();
  TurnOffR();
  delay(delayTime);
  
}

///////////////////////////seconds///////////////////////////////
/////////////L.//////////////////////
void TurnOffR(){
sr.set(0, HIGH);
sr.set(1, HIGH);
sr.set(2, HIGH);
sr.set(3, HIGH);
}
void TurnOnR1(){
sr.set(0, LOW);
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR0(){
sr.set(0, HIGH); 
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR9(){
sr.set(0, LOW);
sr.set(1, HIGH);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR8(){
sr.set(0, HIGH);
sr.set(1, HIGH);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR7(){
sr.set(0, LOW);
sr.set(1, LOW);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR6(){
sr.set(0, HIGH);
sr.set(1, LOW);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR5(){
sr.set(0, LOW);
sr.set(1, HIGH);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR4(){
sr.set(0, HIGH);
sr.set(1, HIGH);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR3(){
sr.set(0, LOW);
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, HIGH);
}
void TurnOnR2(){
sr.set(0, HIGH);
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, HIGH);
}

///////////////////////R////////////////////////////
void TurnOffL(){
sr.set(4, HIGH);
sr.set(5, HIGH);
sr.set(6, HIGH);
sr.set(7, HIGH);
}
void TurnOnL1(){
sr.set(4, LOW);
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL0(){
sr.set(4, HIGH); 
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL9(){
sr.set(4, LOW);
sr.set(5, HIGH);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL8(){
sr.set(4, HIGH);
sr.set(5, HIGH);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL7(){
sr.set(4, LOW);
sr.set(5, LOW);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL6(){
sr.set(4, HIGH);
sr.set(5, LOW);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL5(){
sr.set(4, LOW);
sr.set(5, HIGH);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL4(){
sr.set(4, HIGH);
sr.set(5, HIGH);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL3(){
sr.set(4, LOW);
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, HIGH);
}
void TurnOnL2(){
sr.set(4, HIGH);
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, HIGH);
}
