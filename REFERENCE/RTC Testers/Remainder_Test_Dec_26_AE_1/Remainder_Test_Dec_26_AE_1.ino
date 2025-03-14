

int hours = 9;
int h1 = hours / 10;
int h2 = hours;


void setup() {
  Serial.begin(9600);
  
  h2 %= 10;
  
  
  

}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(hours);
  Serial.println(h1);
  Serial.println(h2);
  delay(1000);

}
