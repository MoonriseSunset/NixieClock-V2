#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;

int hour = 0;
int minute = 0;
int second = 0;
bool h12;
bool PM;


void setup() {
  Serial.begin(9600);
  Wire.begin();

}

void loop() {
  if (second != Clock.getSecond()){
    second = Clock.getSecond();
    minute = Clock.getMinute();
    hour = Clock.getHour(h12, PM);

    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.print(second);
    
    Serial.println("");

    Serial.print(Clock.getHour(h12, PM));
    Serial.print(":");
    Serial.print(Clock.getMinute());
    Serial.print(":");
    Serial.print(Clock.getSecond());

    Serial.println("");
    
  }

}
