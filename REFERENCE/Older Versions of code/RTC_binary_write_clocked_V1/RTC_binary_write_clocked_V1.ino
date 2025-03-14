#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
int hours = 0;   //clock variables
int minutes = 0;
int seconds = 0;
bool h12;
bool PM;
bool Pastnoon = false;

int Lcounter = 1; //IC variable(s)


void setup() {
  pinMode(12,OUTPUT); //IC Signal Setup
  pinMode(11,OUTPUT);

  Wire.begin(); //RTC Communication Setup
  Serial.begin(9600); //For diagnostic purposes, comment out when creating final code
}

void loop() {
 while(Lcounter){
  
  if(Clock.getSecond() != seconds){  //setting clock variables
    hours = (Clock.getHour(h12, PM));

    if (hours > 11, hours != 12){
      hours = hours - 12;
      Pastnoon = true;
    }
    if (hours = 12){
      Pastnoon = true;
    }
    
    minutes = (Clock.getMinute());
    seconds = (Clock.getSecond());
  }
  Serial.print("Hours:");     //All the printing is diagnostic, delete in final version of the code
  Serial.print(hours);
  Serial.println("");
  Serial.print("Minutes:");
  Serial.print(minutes);
  Serial.println("");
  Serial.print("Seconds:");
  Serial.print(seconds);
  Serial.println("");

  int hoursHEX = (hours, HEX);    //Converting the time variables into HEX
  int minutesHEX = (minutes, HEX);
  int secondsHEX = (seconds, HEX);

  Serial.print("Hours in HEX:");  //More diagnostic printing...
  Serial.print(hoursHEX);
  Serial.println("");
  Serial.print("Minutes in HEX:");
  Serial.print(minutesHEX);
  Serial.println("");
  Serial.print("Seconds in HEX:");
  Serial.print(secondsHEX);
  Serial.println("");

  unsigned long ClkPd = 1;
  /*get clock data, in H1H2:M1M2:S1S2 digits, e.g. 12:35:53
  Parse digits into H1,H2...S2
  8bits is a byte, need to put clock digit into byte format
  note that 4 bits is enough to cover 0-9 digit values*/

  //S2 digit
    byte s2 = 0x55;
  //timing frame on pin 11
      digitalWrite(11,HIGH);
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delay(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delay(ClkPd);
      
   //write address of chip for S2
      digitalWrite(12,LOW);
      delay(ClkPd);
      digitalWrite(12,LOW);
      delay(ClkPd);
      digitalWrite(12,HIGH);
      delay(ClkPd);
      
    
  // Shift out s2, MSB first
    for (int i = 4; i < 8; i++){
        if (s2 & 0x80)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        s2 = s2 << 1; 
        delay(ClkPd);  
      }

    for (int i = 0; i < 4; i++){
        if (s2 & 0x80)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        s2 = s2 << 1;
        delay(ClkPd);  
      }
//leave data out high 
   digitalWrite(12, HIGH);
//close timing frame
   digitalWrite(11,LOW);
   delay(5*ClkPd);
 }

}
