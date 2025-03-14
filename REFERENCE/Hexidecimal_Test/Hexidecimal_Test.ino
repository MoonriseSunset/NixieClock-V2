byte seconds = 0;
byte Hseconds;

void setup() {
  Serial.begin(9600);
  while(!Serial){}
  
  

}

void loop() {
  Serial.println(seconds);
  Hseconds = (sprintf("%02X", seconds));
  Serial.println(Hseconds);
  seconds++;
  delay(1000);

}
