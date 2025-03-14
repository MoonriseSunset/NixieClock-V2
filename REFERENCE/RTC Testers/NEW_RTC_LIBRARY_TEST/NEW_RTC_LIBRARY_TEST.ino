#include <DS3231.h>

DS3231 rtc(SDA,SCL);


int hours = 0;
int mins = 0;
int secs = 0;

Time T;



void setup() {
  Serial.begin(9600);
  rtc.begin();

}

void loop() {
  T = rtc.getTime();

  if(secs != T.sec){
    
  
  hours = T.hour;
  mins = T.min;
  secs = T.sec;
  

  Serial.println(hours);
  Serial.println("");
  Serial.println(mins);
  Serial.println("");
  Serial.println(secs);
  Serial.println("");
}
  
  
  
  

}
