#include <DS3231.h>
#include <Wire.h>

int ClkDelay = 400;   //faster delay
//int ClkDelay = 400;
//int ClkDelay = 200;

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
           
           //Serial.begin(9600);  //for diagnostic purposes
           //while(!Serial){}
           
  }

void Reset(){
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  //Serial.println("Reset!");
  //Serial.println("");
   
  
}

void SetAddressA(){
  //ADDRESS A
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
}
void SetAddressB(){
  //ADDRESS B 
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
}
void SetAddressC(){
  //ADDRESS C
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,LOW);
  delayMicroseconds(ClkDelay);
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
}

void FirstFrameSeconds(){
  for (int i = 0; i < 4; i++){
        if (s2 & 1)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift S2 over to look at next bit    
        s2 = s2 >> 1;
        delayMicroseconds(ClkDelay); 
        //Serial.println("First Frame Seconds Done!"); 
         //Serial.println("");
         
      }
}

void SecondFrameSeconds(){
  for (int i = 4; i < 8; i++){
        if (s1 & 1)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        s1 = s1 >> 1; 
        delayMicroseconds(ClkDelay);  
        //Serial.println("Second Frame Seconds Done!"); 
         //Serial.println("");
         
      }
}

void FirstFrameMinutes(){
  for (int i = 0; i < 4; i++){
        if (m2 & 1)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift S2 over to look at next bit    
        m2 = m2 >> 1;
        delayMicroseconds(ClkDelay);  
        //Serial.println("First Frame Minutes Done!"); 
          //Serial.println("");
         
      }
}

void SecondFrameMinutes(){
  for (int i = 4; i < 8; i++){
        if (m1 & 1)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        m1 = m1 >> 1; 
        delayMicroseconds(ClkDelay);  
        //Serial.println("Second Frame Minutes Done!"); 
          //Serial.println("");
         
      }
}

void FirstFrameHours(){
  for (int i = 0; i < 4; i++){
        if (h2 & 1)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift S2 over to look at next bit    
        h2 = h2 >> 1;
        delayMicroseconds(ClkDelay); 
        //Serial.println("First Frame Hours Done!"); 
          //Serial.println("");
          
      }
}

void SecondFrameHours(){
  for (int i = 4; i < 8; i++){
        if (h1 & 1)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        h1 = h1 >> 1; 
        delayMicroseconds(ClkDelay); 
        //Serial.println("Second Frame Done!"); 
          //Serial.println("");
         
      }
}
void EndFrame(){
  digitalWrite(12,HIGH);
  delayMicroseconds(ClkDelay);
  //Serial.println("Frame Ended!");
    //Serial.println("");
   
}
void EndTransmission(){
  digitalWrite(12, HIGH);
  delayMicroseconds(10*ClkDelay);
  //Serial.println("Transmission Ended!");
    //Serial.println("");
   
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
      /*Serial.println("Seconds:");
      Serial.println(seconds);
      Serial.println("Minutes:");
      Serial.println(minutes);
      Serial.println("Hours:");
      Serial.println(hours);*/
      //digitalWrite(11,LOW);
      Reset();                    //FIRST FRAME Seconds
      SetAddressA();
      FirstFrameSeconds();
      EndFrame();
      //digitalWrite(11,HIGH);
      
      //digitalWrite(11,LOW);
      Reset();                    //SECOND FRAME Seconds
      SetAddressA();
      SecondFrameSeconds();
      EndTransmission();
      //digitalWrite(11,HIGH);
      
      //digitalWrite(11,LOW);
      Reset();                    //FIRST FRAME Minutes
      SetAddressB();
      FirstFrameMinutes();
      EndFrame();
      //digitalWrite(11,HIGH);
      
      //digitalWrite(11,LOW);
      Reset();                    //SECOND FRAME Minutes
      SetAddressB();
      SecondFrameMinutes();
      EndTransmission();
      //digitalWrite(11, HIGH);

      //digitalWrite(11, LOW);
      Reset();                    //FIRST FRAME Hours
      SetAddressC();
      FirstFrameHours();
      EndFrame();
      //digitalWrite(11, HIGH);

      //digitalWrite(11, LOW);
      Reset();                    //SECOND FRAME Hours
      SetAddressC();
      SecondFrameHours();
      EndTransmission();
      //digitalWrite(11, HIGH);
     
    }
}
