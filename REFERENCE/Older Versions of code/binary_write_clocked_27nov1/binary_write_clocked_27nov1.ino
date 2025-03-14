
int Lcounter = 1;
int DecCounter = 0;
int HDecCounter = 0;
void setup() 
  {
           pinMode(12,OUTPUT);
           pinMode(11,OUTPUT);
           Serial.begin(9600);
  }

void loop() {
 while(Lcounter == 1){
  
    HDecCounter = int(DecCounter, HEX);
  
    byte a = 0xf1;
    
  // Shift out a, MSB first
    for (int i = 0; i < 8; i++)
      {  
        if (a & 0x80)
          digitalWrite(12, HIGH);
        else
          digitalWrite(12, LOW);
        a = a << 1;
      //delay(5);  
      digitalWrite(11,HIGH);
     // delay(5);
      digitalWrite(11,LOW);
      //delay(10);
      }
    
   digitalWrite(12, LOW);
   //delay(500);
   //digitalWrite(12, HIGH);
   //delay(200);
   //digitalWrite(12, LOW);
   delay(500);

   int DecCounter = DecCounter + 1;
   Serial.println("Hex Digit:");
   Serial.print(HDecCounter);
   
 }

   
}
