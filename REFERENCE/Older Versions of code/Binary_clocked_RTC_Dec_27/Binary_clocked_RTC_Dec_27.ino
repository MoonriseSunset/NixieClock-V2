#include <DS3231.h>
#include <Wire.h>

int ClkDelay = 100;

int hours = 0;      //time variables
int h1 = 0;
int h2 = 0;
int minutes = 0;
int m1 = 0;
int m2 = 0;
int seconds = 0;
int s1 = 0;
int s2 = 0;
bool h12;
bool PM;

DS3231 Clock;


void setup() {
           pinMode(12,OUTPUT);  //for serial chip interface
           pinMode(11,OUTPUT);

           Wire.begin();        //for RTC module
           
           /*Serial.begin(9600);  //for diagnostic purposes
           while(!Serial){}*/
           
  }

void Reset(){
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  
}

void SetAdress(){
  //uncomment address needed

  //ADDRESS A
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);

  //ADDRESS B 
  /*digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);*/

  //ADDRESS C
  /*digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);*/
}
void loop() {
    //S2 digit, reset value every loop
    if(seconds != (Clock.getSecond())){

      seconds = (Clock.getSecond());
      s1 = seconds / 10;
      s2 = seconds;
      s2 %= 10;
      
      minutes = (Clock.getMinute());
      m1 = minutes / 10;
      m2 = minutes;
      m2 %= 10;
      
      hours = (Clock.getHour(h12, PM));
      if(hours > 12){
        hours = hours - 12;
      }
      h1 = hours / 10;
      h2 = hours;
      h2 %= 10;

      Reset();
      digitalWrite(11,HIGH);
      SetAdress();
    }  
  // Shift out s2 4 bits, LSB first

    for (int i = 0; i < 4; i++){
        if (s2 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift S2 over to look at next bit    
        s2 = s2 >> 1;
        delayMicroseconds(ClkDelay);  
      }
      //Stop Bit Frame 1 S2
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      //END FIRST FRAME S2
//timing frame on pin 11
      digitalWrite(11,HIGH);

      
      //START SECOND FRAME S
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
   //write address of chip for S
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
    
  // Shift out s1 next, MSB 4 bits, LSB first
    for (int i = 4; i < 8; i++){
        if (s1 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        s1 = s1 >> 1; 
        delayMicroseconds(ClkDelay);  
      }
      //END SECOND FRAME S1
//leave data out high 
   digitalWrite(12, HIGH);
   delayMicroseconds(10*ClkDelay);

   

   //START DATA FOR M
  //timing frame on pin 11
      digitalWrite(11,HIGH);
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
   //write address of chip for M
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
  // Shift out M2 4 bits, LSB first

    for (int i = 0; i < 4; i++){
        if (m2 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift M2 over to look at next bit    
        m2 = m2 >> 1;
        delayMicroseconds(ClkDelay);  
      }
      //Stop Bit Frame 1 M
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      //END FIRST FRAME M
//timing frame on pin 11
      digitalWrite(11,HIGH);

      
      //START SECOND FRAME M
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
   //write address of chip for M
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
    
  // Shift out M1 next, LSB first
    for (int i = 4; i < 8; i++){
        if (m1 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        m1 = m1 >> 1; 
        delayMicroseconds(ClkDelay);  
      }

      //END SECOND FRAME M
//leave data out high 
   digitalWrite(12, HIGH);
   delayMicroseconds(10*ClkDelay);

   
   //START DATA FOR H
  //timing frame on pin 11
      digitalWrite(11,HIGH);
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
   //write address of chip for M
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
  // Shift out H2 4 bits, LSB first

    for (int i = 0; i < 4; i++){
        if (h2 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift H2 over to look at next bit    
        h2 = h2 >> 1;
        delayMicroseconds(ClkDelay);  
      }
      //Stop Bit Frame 1 H
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      //END FIRST FRAME H
//timing frame on pin 11
      digitalWrite(11,HIGH);

      
      //START SECOND FRAME H
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
   //write address of chip for H
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkDelay);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkDelay);
      
    
  // Shift out H1 next, LSB first
    for (int i = 4; i < 8; i++){
        if (h1 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        h1 = h1 >> 1; 
        delayMicroseconds(ClkDelay);  
      }

      //END SECOND FRAME H
//leave data out high 
   digitalWrite(12, HIGH);
   
//close timing frame
   digitalWrite(11,LOW);
   //delayMicroseconds(20*ClkPd);
   delay(200);
 

}
