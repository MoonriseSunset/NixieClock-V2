#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
int hours = 0;
int minutes = 0;
int seconds = 0;

bool h12;
bool PM;

bool Pastnoon = false;

void setup() {
  Wire.begin(); //initialize connection with RTC module
  Serial.begin(9600); //initialize connection with computer
  
}

void setTime(){
  hours = (Clock.getHour(h12, PM));

    if (hours > 11, hours != 12){
      hours = 12 - hours;
      Pastnoon = true;
    }
    if (hours = 12){
      Pastnoon = true;
    }
    
    minutes = (Clock.getMinute());
    seconds = (Clock.getSecond());
}

void Display(){
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
      
    }
    else{
      Serial.print(seconds);
      }
    
    if (Pastnoon == true){
      Serial.print("PM");
      Serial.println("");
    }
    else{
      Serial.print("AM");
      Serial.println("");
    }
  
}
void loop() {
  
  if(Clock.getSecond() != seconds){
    
    setTime();
    Display();

    
  }
   
}
