#include <DS3231.h>
#include <LiquidCrystal.h>

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DS3231  rtc(SDA, SCL);
int hours = 0;
int minutes = 0;
int seconds = 0;
Time t;
bool PM = false;


void setup() {
  // put your setup code here, to run once:
  rtc.begin();
  lcd.begin(16, 2);
}

void loop() {
  PM = false;
  t = rtc.getTime();
  
  lcd.clear();
  hours = t.hour;
  minutes = t.min;
  seconds = t.sec;
  if(hours > 12){
    hours = hours - 12;
    PM = true;
  }

  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds);
  if(PM = true){
    lcd.print("PM");
  }
  else{
    lcd.print("AM");
  }
 delay(500);
}
