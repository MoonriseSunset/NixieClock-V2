#include <DS3231.h>
#include <Wire.h>

int seconds = 0;
int s1 = 0;
int s2 = 0;

int minutes = 0;
int m1 = 0;
int m2 = 0;

int hours = 0;
int h1 = 0;
int h2 = 0;

bool h12;
bool PM;

DS3231 Clock;

void setup() {
  
  Serial.begin(9600);
  Wire.begin();
  
}
void loop() {
  

  if (seconds != Clock.getSecond()){
    
  seconds = (Clock.getSecond());
  minutes = (Clock.getMinute());
  hours = (Clock.getHour(h12, PM));
  
  s1 = seconds / 10;
  s2 = seconds;
  s2 %= 10;

  m1 = minutes / 10;
  m2 = minutes;
  m2 %= 10;

  

  if (hours > 12){
    hours = hours - 12;
  }
  
  h1 = hours / 10;
  h2 = hours;
  h2 %= 10;
  

  
    
  
  Serial.print("Time:");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  Serial.println("");
  Serial.println("");

  Serial.print("Seconds 1st digit:");
  Serial.print(s1);
  
  Serial.println("");
  
  Serial.print("Seconds 2nd digit:");
  Serial.print(s2);
  
  Serial.println("");
  Serial.println("");
  
  Serial.print("Minutes 1st digit:");
  Serial.print(m1);
  
  Serial.println("");
  
  Serial.print("Minutes 2nd digit:");
  Serial.print(m2);
  
  Serial.println("");
  Serial.println("");
  
  Serial.print("Hours 1st digit:");
  Serial.print(h1);
  
  Serial.println("");
  
  Serial.print("Hours 2nd digit:");
  Serial.print(h2);
  
  Serial.println("");
  Serial.println("");

  
  
  
  }
}
