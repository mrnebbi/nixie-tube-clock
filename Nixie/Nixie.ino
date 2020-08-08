/*
 * Nixie tube setup
 */

  #include <ShiftRegister74HC595.h>
  
  // create shift register object (number of shift registers, data pin, clock pin, latch pin)
  ShiftRegister74HC595<1> ShiftHrs (7, 8, 9); 
  ShiftRegister74HC595<1> ShiftMins (4, 5, 6);

  // clock stuff. these are needed for the DS3231 module.
  #include <DS3231.h>
  #include <Wire.h>  // I2C

  DS3231 Clock;

  bool h12;
  bool PM;
  

  int delayTime = 2000;//250;
  int testTime = 1000;
  int shortDelayTime = 2000;//150;
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
  const int fetchDuration = 300; // every X seconds
  bool cycleOnBoot = true;
  bool tubeTestMode = false;
  
  int mode = 0;
  int countHr = 0;
  int countMin = 0;
  bool setTimeNextLoop = false; // Issuing I2C commands during the interrupt function seems to cause a crash. This provides a workaround.
  bool beginTimeSetNextLoop = false; // Issuing I2C commands during the interrupt function seems to cause a crash. This provides a workaround.

  
  bool blinkState = false;
  unsigned long previousMillis = 0; // Interrupt timer for debouncing

  // time keeping
  int currentTimeHr = 0;
  int currentTimeMin = 0;
  int currentTimeSec = 0;
  int fetchCount = 0;

/*
 * Setup function
 */

void setup() {
  // put your setup code here, to run once:
  pinMode(setButton, INPUT_PULLUP);
  pinMode(addButton, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(setButton),setButtonPress,FALLING);
  attachInterrupt(digitalPinToInterrupt(addButton),addButtonPress,FALLING);

  /*
   * Serial connection
   * 
   * RX - Grey
   * TX - Orange
   * RST - Yellow
   * GND - Black
   * 5V - Red
   * 
   */

  Serial.begin(115200);
  Serial.println("Start");

  if (tubeTestMode) {
    tubeTest();
  }
  
  if (cycleOnBoot) {
    cycleTubes();
  }

  Wire.begin();

  Clock.setClockMode(false);  // set to 24h
  fetchCurrentTime();
}

void loop() {
  
  // these functions run once every second
  
  if ((unsigned long)(millis() - previousMillis) >= 1000) {
    previousMillis = millis();
    fetchCount = fetchCount + 1;
    countTime();
    
    if (mode == 0) {
      showCurrentTime();
    } else {
      showSetTime();
    }
  }


  // these function run every loop

   if (beginTimeSetNextLoop) {
    beginTimeSetNextLoop = false;
    flashTime(2);
  }

  if (tubeTestMode) {
    tubeTest();
    tubeTestMode = false;
  }
  
  if (setTimeNextLoop) {
    Clock.setClockMode(false);  // set to 24h
    Clock.setHour(countHr);
    Clock.setMinute(countMin);
    Clock.setSecond(0);
    currentTimeHr = Clock.getHour(h12, PM);
    currentTimeMin = Clock.getMinute();
    currentTimeSec = Clock.getSecond();
    setTimeNextLoop = false;
    flashTime(3);
  }

  if(fetchCount >= fetchDuration) {
    fetchCurrentTime();
    fetchCount = 0;
  }
}


// keep a track of the time ourselves so we don't have to poll the rtc so often
void countTime() {
  currentTimeSec = (currentTimeSec == 59) ? 0 : currentTimeSec + 1;
  
  if(currentTimeSec == 0) currentTimeMin = currentTimeMin == 59 ? 0 : currentTimeMin + 1;
  if(currentTimeSec == 0 && currentTimeMin == 0) currentTimeHr = currentTimeHr == 23 ? 0 : currentTimeHr + 1;
}

void fetchCurrentTime() {
  Serial.println("Get time");
  currentTimeHr = Clock.getHour(h12, PM);
  currentTimeMin = Clock.getMinute();
  currentTimeSec = Clock.getSecond();
}

void showCurrentTime() {
    if (currentTimeHr < 10) {
      Serial.print("0");
    }
    Serial.print(currentTimeHr);
    Serial.print(":");
    if (currentTimeMin < 10) {
      Serial.print("0");
    }
    Serial.print(currentTimeMin);
    Serial.print(":");
    if (currentTimeSec < 10) {
      Serial.print("0");
    }
    Serial.print(currentTimeSec);

    int hr1 = (currentTimeHr / 10) % 10;
    int hr2 = currentTimeHr % 10;

    int min1 = (currentTimeMin / 10) % 10;
    int min2 = currentTimeMin % 10;

    int sec1 = (currentTimeSec / 10) % 10;
    int sec2 = currentTimeSec % 10;

    setDigit(2,hr1);
    setDigit(3,hr2);
    setDigit(0,min1);
    setDigit(1,min2);

    Serial.print(" (A:");
    Serial.print(hr1);
    Serial.print(" B:");
    Serial.print(hr2);
    Serial.print(" C:");
    Serial.print(min1);
    Serial.print(" D:");
    Serial.print(min2);
    Serial.print(" E:");
    Serial.print(sec1);
    Serial.print(" F:");
    Serial.print(sec2);
    Serial.println(")");

    // Cycle tubes at midnight
    if ((currentTimeHr == 0 && currentTimeMin == 0 && currentTimeSec == 0) || (currentTimeHr == 6 && currentTimeMin == 0 && currentTimeSec == 0) || (currentTimeHr == 12 && currentTimeMin == 0 && currentTimeSec == 0)) {
      cycleTubes();
      fetchCurrentTime();
    }
}

void showSetTime() {
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

    if (mode != 2) {
      setDigit(2,hr1);
      setDigit(3,hr2);
      clearDigit(0);
      clearDigit(1);
    }

    if (mode != 1) {
      setDigit(0,min1);
      setDigit(1,min2);
      clearDigit(2);
      clearDigit(3);
    }
    
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
  
  showSetTime();
}

void addMin(){

  if (countMin >= 59) {
    countMin = 0;
  } else {
    countMin = countMin + 1;
  }

  showSetTime();
}


// Handle button presses and pass off to setter functions

void setButtonPress(){
  if ((unsigned long)(millis() - previousMillis) >= 500) {
    previousMillis = millis();
    
    if (digitalRead(addButton) && mode == 0) {
      Serial.println("Test Tubes");
      tubeTestMode = true;
    } else {
      if (mode > 1) {
        mode = 0;
      } else {
        mode = mode + 1;
      }
  
      switch (mode) {
        case 1:
          beginTimeSetNextLoop = true;
          countHr = currentTimeHr;
          countMin = currentTimeMin;
          break;
        case 2:
          break;
        default:
          // revert to time display
          setTimeNextLoop = true;
          break;
      }
  
      Serial.print("New mode: ");
      Serial.println(mode);
    }
  }
}

void addButtonPress(){
//  Serial.println("Add");


    if ((unsigned long)(millis() - previousMillis) >= 200) {
      previousMillis = millis();
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
 * setDigit(position, digit)
 * Position: 0 & 1 = hours. 2 & 3 = minutes
 * Digit: What digit to show? 0 - 9
 */

void setDigit(int position, int digit){
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
 * clearDigit(position)
 * Clear a digit at a specific position. Shows no digit.
 * Position: 0 & 1 = hours. 2 & 3 = minutes
 */
 
void clearDigit(int position){
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
 * clearAll()
 * Clears all digits at once. Shows no digits.
 */

void clearAll() {
  clearDigit(0); // hr 1
  clearDigit(1); // hr 2
  clearDigit(2); // min 1
  clearDigit(3); // min 2
}

/*
 * cycleTubes()
 * Runs all digits through all Nixie tubes to prevent cathode poisoning
 */

void cycleTubes() {
  Serial.println("Cycle tubes");
  for (int x = 0; x < 10; x++) {
    setDigit(0,x);
    setDigit(1,x);
    setDigit(2,x);
    setDigit(3,x);
    delay(delayTime);
  }
  clearAll();
  delay(delayTime);
}



void tubeTest() {
  clearAll();
  Serial.println("Test tubes");
  for (int x = 0; x < 10; x++) {
    setDigit(0,x);
    setDigit(1,x);
    setDigit(2,x);
    setDigit(3,x);
    Serial.print("All tubes: ");
    Serial.println(x);
    delay(testTime);
  }
  Serial.println("CLEAR");
  clearAll();
  
  
  delay(testTime);
  for (int x = 0; x < 10; x++) {
    setDigit(1,x);
    Serial.print("Minute 1: ");
    Serial.println(x);
    delay(testTime);
  }
  Serial.println("CLEAR");
  clearAll();

  
  delay(testTime);
  for (int x = 0; x < 10; x++) {
    setDigit(0,x);
    Serial.print("Minute 2: ");
    Serial.println(x);
    delay(testTime);
  }
  Serial.println("CLEAR");
  clearAll();



  delay(testTime);
  for (int x = 0; x < 10; x++) {
    setDigit(3,x);
    Serial.print("Hour 1: ");
    Serial.println(x);
    delay(testTime);
  }
  Serial.println("CLEAR");
  clearAll();
  
  delay(testTime);
  for (int x = 0; x < 10; x++) {
    setDigit(2,x);
    Serial.print("Hour 2: ");
    Serial.println(x);
    delay(testTime);
  }
  Serial.println("CLEAR");
  clearAll();


  
  delay(testTime);
}


void flashTime(int count) {
  for (int x = 0; x < count; x++) {
    clearAll();
    delay(500);
    showCurrentTime();
    delay(500);
  }
}
