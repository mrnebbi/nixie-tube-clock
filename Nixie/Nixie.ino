/*
 * Nixie tube setup
 */

  #include <ShiftRegister74HC595.h>
  
  // create shift register object (number of shift registers, data pin, clock pin, latch pin)
  ShiftRegister74HC595 ShiftHrs (1, 4, 5, 6); 
  ShiftRegister74HC595 ShiftMins (1, 6, 7, 8);
  
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


/*
 * Date/time & button setup
 */
  
  const int setButton = 2;
  const int addButton = 3;
  
  int mode = 0;
  int countHr = 0;
  int countMin = 0;
  
  bool blinkState = false;
  unsigned long time_now = 0; // Interrupt timer for debouncing


/*
 * Setup function
 */

void setup() {
  
  // put your setup code here, to run once:
  pinMode(setButton, INPUT_PULLUP);
  pinMode(addButton, INPUT_PULLUP);


  Serial.begin(115200);
  Serial.println("Start");
  
  attachInterrupt(digitalPinToInterrupt(setButton),setButtonPress,FALLING);
  attachInterrupt(digitalPinToInterrupt(addButton),addButtonPress,FALLING);

}

void loop() {
  if (mode == 0) {
    showTime();
  }
  delay(500);
}


void showTime() {
    if (countHr < 10) {
      Serial.print("0");
    }
    Serial.print(countHr);
    Serial.print(":");
    if (countMin < 10) {
      Serial.print("0");
    }
    Serial.print(countMin);

    int hr1 = (countHr / 10) % 10;
    int hr2 = countHr % 10;

    int min1 = (countMin / 10) % 10;
    int min2 = countMin % 10;

    Serial.print(" (A:");
    Serial.print(hr1);
    Serial.print(" B:");
    Serial.print(hr2);
    Serial.print(" C:");
    Serial.print(min1);
    Serial.print(" D:");
    Serial.print(min2);
    Serial.println(")");
}

void addHour(){

  if (countHr >= 23) {
    countHr = 0;
  } else {
    countHr = countHr + 1;
  }
  
  showTime();
}

void addMin(){

  if (countMin >= 59) {
    countMin = 0;
  } else {
    countMin = countMin + 1;
  }

  showTime();
}


// Handle button presses and pass off to setter functions

void setButtonPress(){
//  Serial.println("Set");
  if(millis() > time_now + 200){
    time_now = millis();
    
    if (mode > 1) {
      mode = 0;
    } else {
      mode = mode + 1;
    }

        
    switch (mode) {
      case 1:
          // flash hours
        break;
      case 2:
          // flash mins
        break;
      default:
          // revert to time display
        break;
    }
    
  }
}

void addButtonPress(){
//  Serial.println("Add");
  if(millis() > time_now + 200){
    time_now = millis();
    if (mode == 1) {
      addHour();
    } else if (mode == 2) {
      addMin();
    }
  }
}



/*
 * Functions to drive Nixie Tubes
 */

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


