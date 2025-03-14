#include<DS3231.h>
#include<Wire.h>        //Clock library

int Lcounter = 1;
int Bitlength = 200;  //set bit length in microseconds
byte s2 = 0xf0;       //hexidecimal digit being used


void setup() {
           pinMode(12,OUTPUT);
           pinMode(11,OUTPUT);
  }

void setAddressA() {              //first serial parallel address
  digitalWrite(12,LOW);
  delayMicroseconds(Bitlength);
  digitalWrite(12,LOW);
  delayMicroseconds(Bitlength);
  digitalWrite(12,HIGH);
  delayMicroseconds(Bitlength);
  
}

void setAddressB() {             //second serial parallel address
  digitalWrite(12,LOW);
  delayMicroseconds(Bitlength);
  digitalWrite(12,HIGH);
  delayMicroseconds(Bitlength);
  digitalWrite(12,LOW);
  delayMicroseconds(Bitlength);
  
}

void setAddressC() {           //third serial parallel address
  digitalWrite(12,LOW);
  delayMicroseconds(Bitlength);
  digitalWrite(12,HIGH);
  delayMicroseconds(Bitlength);
  digitalWrite(12,HIGH);
  delayMicroseconds(Bitlength);
  
}

void startTransmission(){
  digitalWrite(12,LOW);  
  delayMicroseconds(Bitlength);
  digitalWrite(12,HIGH);
  delayMicroseconds(Bitlength);
}

void FirstFrame(){
  for (int i = 0; i < 4; i++){
        if (s2 & 0x01)
          digitalWrite(12, HIGH);
          
        else
          digitalWrite(12, LOW);
      //Shift S2 over to look at next bit    
        s2 = s2 >> 1;
        delayMicroseconds(Bitlength);  
      }
}

void SecondFrame(){
  for (int i = 4; i < 8; i++){
        if (s2 & 0x01)
          digitalWrite(12, HIGH);
          
        else
          digitalWrite(12, LOW);
        //shift s2 over 1 bit  
        s2 = s2 >> 1; 
        delayMicroseconds(Bitlength);  
      }
}
void loop() {
 
    
    

  
      digitalWrite(11,HIGH);  //for the osilloscope
      
      startTransmission(); //start bits (ST0 and ST1)
      
   //write address of chip that is sending out info (s2)
      setAddressA();
      
  // Shift out s2 first 4 bits
      FirstFrame();
      

    
      //Stop Bit Frame 1 S2
      digitalWrite(12,HIGH);
      delayMicroseconds(Bitlength);    //end or reset bit
      
      digitalWrite(11,HIGH);

      
      //start second frame of data:
      startTransmission();
      
   //write address of chip for S2
      setAddressA();
      
    
  // Shift out s2 next, MSB 4 bits, LSB first
      SecondFrame();


      //END SECOND FRAME S2
//leave data out high 
   digitalWrite(12, HIGH);
//close timing frame
   digitalWrite(11,LOW);
   delayMicroseconds(5*Bitlength);
 }
