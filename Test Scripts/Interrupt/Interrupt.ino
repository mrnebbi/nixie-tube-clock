// Pin setup
const int setButton = 2;
const int addButton = 3;

int mode = 0;
int countHr = 0;
int countMin = 0;

// Interrupt timer for debouncing
unsigned long time_now = 0;

void setup() {
  
  // put your setup code here, to run once:
  pinMode(setButton, INPUT_PULLUP);
  pinMode(addButton, INPUT_PULLUP);


  Serial.begin(115200);
  Serial.println("Interrupt test");
  
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
    Serial.println(countMin);
}

void addHour(){

  if (countHr > 23) {
    countHr = 0;
  } else {
    countHr = countHr + 1;
  }
  
  showTime();
}

void addMin(){

  if (countMin > 59) {
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

