#include <ArduinoJson.h>

#include <Wire.h>  // I2C
#include <Time.h>  // Time Manipulation
#include <TimeAlarms.h>
#include <DS3232RTC.h>

// This code is required for bluetooth definitions

#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);



//int weekStart = 1;
//bool debug = true;
//char* weekDays[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};


void setup() {
  Wire.begin(); // Begin I2C
  Serial.begin(9600); // Start Serial comms
  Serial.println("\nNixie v1.1"); // Dump version information
  setSyncProvider(RTC.get);
  
  
  //Alarm.alarmRepeat(19,45,0, testAlarm);
  
  
  // Setup the BLE broadcast
  
  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  uart.setDeviceName("TANGO"); /* 7 characters max! */
  uart.begin();
}

void testAlarm(){
  Serial.println("Alarm");
}


// Send simple strings using UART
void sendBlMsg(String msg) {
  String s = msg;
  uint8_t sendBuffer[20];
  s.getBytes(sendBuffer,20);
  char sendbuffersize = min(20, s.length());
  
  uart.write(sendBuffer, sendbuffersize); 
}


void loop() {
  Serial.print(day());
  Serial.print('-');
  Serial.print(month());
  Serial.print('-');
  Serial.print(year());
  Serial.print(' ');
  
  Serial.print(hour());
  Serial.print(':');
  Serial.print(minute());
  Serial.print(':');
  Serial.println(second());
  Alarm.delay(1000);
  
  // Continue polling for BLE connections
  uart.pollACI();
  
  
  String blRead = "";
  while (uart.available()) {
    char c = uart.read();
    blRead += c;
  }
  
  if (blRead != "") {
    
    if (blRead.startsWith("t(") && blRead.endsWith(")")) {
      Serial.print("\n\n\n");
      Serial.print("Set time");
      String newTime = blRead.substring(2,10);
      Serial.print(newTime);
      setTimeX(newTime);
      Serial.print("\n\n\n");
    }
    
    if (blRead.startsWith("d(") && blRead.endsWith(")")) {
      Serial.print("\n\n\n");
      Serial.print("Set date");
      String newDate = blRead.substring(2,10);
      Serial.print(newDate);
      setDateX(newDate);
      Serial.print("\n\n\n");
    }
    
    blRead = "";
  }
  
  if (Serial.available()) {
      // Read a line from Serial
      Serial.setTimeout(100); // 100 millisecond timeout
      String s = Serial.readString();
   // We need to convert the line to bytes, no more than 20 at this time
      uint8_t sendbuffer[20];
      s.getBytes(sendbuffer, 20);
      char sendbuffersize = min(20, s.length());

      Serial.print(F("\n* Sending -> \"")); Serial.print((char *)sendbuffer); Serial.println("\"");
      
      // write the data
      uart.write(sendbuffer, sendbuffersize);
    }
}


// This function allows you to set the realtime clock

void setClock(int yr,int mon,int dy,int hr,int mins, int secs) {
  time_t t;
  tmElements_t tm;
  
  
  
  tm.Year = yr;
  tm.Month = mon;
  tm.Day = dy;
  
  tm.Hour = hr;
  tm.Minute = mins;
  tm.Second = secs;
  t = makeTime(tm);
  RTC.set(t);
}


void setTimeX(String newTime) {
  time_t t;
  tmElements_t tm;
  
   if (year() >= 1000)
    tm.Year = CalendarYrToTm(year());
  else
    tm.Year = y2kYearToTm(year());
  
  tm.Month = month();
  tm.Day = day();
  
  int newHr = newTime.substring(0,2).toInt();
  int newMins = newTime.substring(3,5).toInt();
  int newSecs = newTime.substring(6,8).toInt();
  
  tm.Hour = newHr;
  tm.Minute = newMins;
  tm.Second = newSecs;
  
  t = makeTime(tm);
  RTC.set(t);
  setTime(t);
  
  setSyncProvider(RTC.get);
  
  sendBlMsg("Set time to " + String(newHr) + ":" + String(newMins) + ":" + String(newSecs));
  
};





void setDateX(String newDate) {
  time_t t;
  tmElements_t tm;
  
  int newYr = newDate.substring(0,2).toInt();
  int newMo = newDate.substring(4,5).toInt();
  int newDy = newDate.substring(6,8).toInt();
  
  Serial.print("Year: ");
  Serial.println(newYr);
  
  Serial.print("Month: ");
  Serial.println(newMo);
  
  Serial.print("Day: ");
  Serial.println(newDy);
  
  if (newYr >= 1000)
    tm.Year = CalendarYrToTm(newYr);
  else
    tm.Year = y2kYearToTm(newYr);
  
  tm.Month = newMo;
  tm.Day = newDy;
  
  tm.Hour = hour();
  tm.Minute = minute();
  tm.Second = second();
  
  
  Serial.print("Hour: ");
  Serial.println(hour());
  
  Serial.print("Minute: ");
  Serial.println(minute());
  
  Serial.print("Second: ");
  Serial.println(second());
  
  
  t = makeTime(tm);
  RTC.set(t);
  setTime(t);
  
  setSyncProvider(RTC.get);
  
  sendBlMsg("Set date to " + String(newDy) + "-" + String(newMo) + "-" + String(newYr));
};



void aciCallback(aci_evt_opcode_t event)
{
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Advertising Bluetooth"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected"));
      break;
    default:
      break;
  }
}



// This function receives bluetooth data

void rxCallback(uint8_t *buffer, uint8_t len)
{


  
/*
  char ca = buffer[0];
  
  if (buffer[0] == 's') {
    Serial.println("Begin time set");
  }
  */
  
  
  
  /* Echo the same data back! */
  //uart.write(buffer, len);
}




