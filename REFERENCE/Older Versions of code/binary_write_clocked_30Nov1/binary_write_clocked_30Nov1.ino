
//include clock libraries
int Lcounter = 1;
//note max chip rate is 24kbps

void setup() {
           pinMode(12,OUTPUT);
           pinMode(11,OUTPUT);
  }

void loop() {
    //S2 digit, reset value every loop

 while(Lcounter){
 int ClkPd = 100;
  //get clock data, in H1H2:M1M2:S1S2 digits, e.g. 12:35:53
  //Parse digits into H1,H2...S2
  //8bits is a byte, need to put clock digit into byte format
  //note that 4 bits is enough to cover 0-9 digit values

  // digit values, reset value every loop
   byte s2 = 0x05;
   byte s1 = 0x05;
   byte m2 = 0x05;
   byte m1 = 0x05;
   byte h2 = 0x05;
   byte h1 = 0x05;
   
  //timing frame on pin 11
      digitalWrite(11,HIGH);
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
   //write address of chip for S
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
  // Shift out s2 4 bits, LSB first

    for (int i = 0; i < 4; i++){
        if (s2 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift S2 over to look at next bit    
        s2 = s2 >> 1;
        delayMicroseconds(ClkPd);  
      }
      //Stop Bit Frame 1 S2
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      //END FIRST FRAME S2
//timing frame on pin 11
      digitalWrite(11,HIGH);

      
      //START SECOND FRAME S
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
   //write address of chip for S
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
    
  // Shift out s1 next, MSB 4 bits, LSB first
    for (int i = 4; i < 8; i++){
        if (s1 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        s1 = s1 >> 1; 
        delayMicroseconds(ClkPd);  
      }
      //END SECOND FRAME S1
//leave data out high 
   digitalWrite(12, HIGH);
   delayMicroseconds(10*ClkPd);

   

   //START DATA FOR M
  //timing frame on pin 11
      digitalWrite(11,HIGH);
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
   //write address of chip for M
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
  // Shift out M2 4 bits, LSB first

    for (int i = 0; i < 4; i++){
        if (m2 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift M2 over to look at next bit    
        m2 = m2 >> 1;
        delayMicroseconds(ClkPd);  
      }
      //Stop Bit Frame 1 M
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      //END FIRST FRAME M
//timing frame on pin 11
      digitalWrite(11,HIGH);

      
      //START SECOND FRAME M
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
   //write address of chip for M
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
    
  // Shift out M1 next, LSB first
    for (int i = 4; i < 8; i++){
        if (m1 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        m1 = m1 >> 1; 
        delayMicroseconds(ClkPd);  
      }

      //END SECOND FRAME M
//leave data out high 
   digitalWrite(12, HIGH);
   delayMicroseconds(10*ClkPd);

   
   //START DATA FOR H
  //timing frame on pin 11
      digitalWrite(11,HIGH);
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
   //write address of chip for M
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
  // Shift out H2 4 bits, LSB first

    for (int i = 0; i < 4; i++){
        if (h2 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
      //Shift H2 over to look at next bit    
        h2 = h2 >> 1;
        delayMicroseconds(ClkPd);  
      }
      //Stop Bit Frame 1 H
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      //END FIRST FRAME H
//timing frame on pin 11
      digitalWrite(11,HIGH);

      
      //START SECOND FRAME H
  //write out two bits for chip_clock:ST0,ST1
  //first ST0 goes low
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
  //then ST1 goes high
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
   //write address of chip for H
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      digitalWrite(12,LOW);
      delayMicroseconds(ClkPd);
      digitalWrite(12,HIGH);
      delayMicroseconds(ClkPd);
      
    
  // Shift out H1 next, LSB first
    for (int i = 4; i < 8; i++){
        if (h1 & 0x01)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
          
        h1 = h1 >> 1; 
        delayMicroseconds(ClkPd);  
      }

      //END SECOND FRAME H
//leave data out high 
   digitalWrite(12, HIGH);
   
//close timing frame
   digitalWrite(11,LOW);
   //delayMicroseconds(20*ClkPd);
   delay(200);
 }

}
