#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
int hours = 0;
int minutes = 0;
int seconds = 0;

bool h12;
bool PM;
bool digits = false;

void setup() {
  Wire.begin(); //initialize connection with RTC module
  Serial.begin(9600); //initialize connection with computer
  
}

void loop() {
  
  hours = (Clock.getHour(h12, PM));

  if (hours > 11){
    hours = hours - 12;
  }
  minutes = (Clock.getMinute());
  seconds = (Clock.getSecond());

  Serial.print(hours);
  Serial.print(":");
  
  if (minutes < 10){
    Serial.print("0");
    Serial.print(minutes);
    Serial.print(":");
  }
  else{
    Serial.print(minutes);
    Serial.print(":");
  }

  if (seconds < 10){
    Serial.print("0");
    Serial.print(seconds);
    Serial.println("");
  }
  else{
    Serial.print(seconds);
    Serial.println("");
  }

  
  
  


  delay(1000);
}
