const int Binout = 7;
int BinDelay = 500;
int BinaryDig = B10011;
void setup() {
  // put your setup code here, to run once:
  pinMode(Binout, OUTPUT);
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  while(BinDelay > 1){
   digitalWrite(Binout, HIGH);
  delay(BinDelay);
  digitalWrite(Binout, LOW);
  delay(BinDelay);
  BinDelay = BinDelay -2;
  
  }
  

}
