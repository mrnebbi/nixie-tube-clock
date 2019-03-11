/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (1, 2, 3, 4); 
ShiftRegister74HC595 srM (1, 5, 6, 7);

int delayTime = 1000;

void setup() { 
}

void loop() {
  TurnOnR9();
  TurnOnL9();
  TurnOnML1();
  TurnOnMR1();
  delay(delayTime);
  TurnOffL();
  TurnOffR();
  TurnOffML();
  TurnOffMR();
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
void TurnOnR0(){
sr.set(0, LOW); 
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR1(){
sr.set(0, HIGH);
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR2(){
sr.set(0, LOW);
sr.set(1, HIGH);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR3(){
sr.set(0, HIGH);
sr.set(1, HIGH);
sr.set(2, LOW);
sr.set(3, LOW);
}
void TurnOnR4(){
sr.set(0, LOW);
sr.set(1, LOW);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR5(){
sr.set(0, HIGH);
sr.set(1, LOW);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR6(){
sr.set(0, LOW);
sr.set(1, HIGH);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR7(){
sr.set(0, HIGH);
sr.set(1, HIGH);
sr.set(2, HIGH);
sr.set(3, LOW);
}
void TurnOnR8(){
sr.set(0, LOW);
sr.set(1, LOW);
sr.set(2, LOW);
sr.set(3, HIGH);
}
void TurnOnR9(){
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
void TurnOnL0(){
sr.set(4, LOW); 
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL1(){
sr.set(4, HIGH);
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL2(){
sr.set(4, LOW);
sr.set(5, HIGH);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL3(){
sr.set(4, HIGH);
sr.set(5, HIGH);
sr.set(6, LOW);
sr.set(7, LOW);
}
void TurnOnL4(){
sr.set(4, LOW);
sr.set(5, LOW);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL5(){
sr.set(4, HIGH);
sr.set(5, LOW);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL6(){
sr.set(4, LOW);
sr.set(5, HIGH);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL7(){
sr.set(4, HIGH);
sr.set(5, HIGH);
sr.set(6, HIGH);
sr.set(7, LOW);
}
void TurnOnL8(){
sr.set(4, LOW);
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, HIGH);
}
void TurnOnL9(){
sr.set(4, HIGH);
sr.set(5, LOW);
sr.set(6, LOW);
sr.set(7, HIGH);
}














///////////////////////////seconds///////////////////////////////
/////////////L.//////////////////////
void TurnOffMR(){
srM.set(0, HIGH);
srM.set(1, HIGH);
srM.set(2, HIGH);
srM.set(3, HIGH);
}
void TurnOnMR0(){
srM.set(0, LOW); 
srM.set(1, LOW);
srM.set(2, LOW);
srM.set(3, LOW);
}
void TurnOnMR1(){
srM.set(0, HIGH);
srM.set(1, LOW);
srM.set(2, LOW);
srM.set(3, LOW);
}
void TurnOnMR2(){
srM.set(0, LOW);
srM.set(1, HIGH);
srM.set(2, LOW);
srM.set(3, LOW);
}
void TurnOnMR3(){
srM.set(0, HIGH);
srM.set(1, HIGH);
srM.set(2, LOW);
srM.set(3, LOW);
}
void TurnOnMR4(){
srM.set(0, LOW);
srM.set(1, LOW);
srM.set(2, HIGH);
srM.set(3, LOW);
}
void TurnOnMR5(){
srM.set(0, HIGH);
srM.set(1, LOW);
srM.set(2, HIGH);
srM.set(3, LOW);
}
void TurnOnMR6(){
srM.set(0, LOW);
srM.set(1, HIGH);
srM.set(2, HIGH);
srM.set(3, LOW);
}
void TurnOnMR7(){
srM.set(0, HIGH);
srM.set(1, HIGH);
srM.set(2, HIGH);
srM.set(3, LOW);
}
void TurnOnMR8(){
srM.set(0, LOW);
srM.set(1, LOW);
srM.set(2, LOW);
srM.set(3, HIGH);
}
void TurnOnMR9(){
srM.set(0, HIGH);
srM.set(1, LOW);
srM.set(2, LOW);
srM.set(3, HIGH);
}


///////////////////////R////////////////////////////
void TurnOffML(){
srM.set(4, HIGH);
srM.set(5, HIGH);
srM.set(6, HIGH);
srM.set(7, HIGH);
}
void TurnOnML0(){
srM.set(4, LOW); 
srM.set(5, LOW);
srM.set(6, LOW);
srM.set(7, LOW);
}
void TurnOnML1(){
srM.set(4, HIGH);
srM.set(5, LOW);
srM.set(6, LOW);
srM.set(7, LOW);
}
void TurnOnML2(){
srM.set(4, LOW);
srM.set(5, HIGH);
srM.set(6, LOW);
srM.set(7, LOW);
}
void TurnOnML3(){
srM.set(4, HIGH);
srM.set(5, HIGH);
srM.set(6, LOW);
srM.set(7, LOW);
}
void TurnOnML4(){
srM.set(4, LOW);
srM.set(5, LOW);
srM.set(6, HIGH);
srM.set(7, LOW);
}
void TurnOnML5(){
srM.set(4, HIGH);
srM.set(5, LOW);
srM.set(6, HIGH);
srM.set(7, LOW);
}
void TurnOnML6(){
srM.set(4, LOW);
srM.set(5, HIGH);
srM.set(6, HIGH);
srM.set(7, LOW);
}
void TurnOnML7(){
srM.set(4, HIGH);
srM.set(5, HIGH);
srM.set(6, HIGH);
srM.set(7, LOW);
}
void TurnOnML8(){
srM.set(4, LOW);
srM.set(5, LOW);
srM.set(6, LOW);
srM.set(7, HIGH);
}
void TurnOnML9(){
srM.set(4, HIGH);
srM.set(5, LOW);
srM.set(6, LOW);
srM.set(7, HIGH);
}


