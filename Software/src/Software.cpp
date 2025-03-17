/*
* NIXIE CLOCK ITERATION 2 MAINCODE
* Author: MoonriseSunset
* Last Modified: 3/16/2025
*/

// Include Particle libraries (needed for RTC and Wifi)
#include "Particle.h"

// Particle-related setup functions (no idea what they fully do)
SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);



// Variable declarations ---------------------------------------------

//CONSTANTS ---------

//400 microsecond timing delay for data line to serial chips
const int CLK_DELAY = 400;

//set level of debugging, 0 for nothing, 1 for high level functions, 2 for everything
const int DEBUG = 0;

//enable/disable oscilloscope trigger, 0 is disabled, 1 is enabled
const int EN_OSC = 1;

// 24-hour mode, 0 is disabled, 1 is enabled
const int HOUR_FORMAT = 0;


//GLOBAL VARIABLES ---------

//Time variables to hold current time
//Time variables are initially set to -1 to force them to be updated
int seconds = -1, minutes = -1, hours = -1;


//PIN DECLARATIONS ---------

//On nano every, dataline was on pin 12, on photon the data pin is now D6
const int DATA_LINE = 6;

//Oscilloscope trigger pin for debugging
const int SCOPE_TRIGGER = 5;

//Debug indicator LED
const int DEBUG_INDICATOR = 7;

// Function declarations ---------------------------------------------
//NOTE: To find the definitions, scroll past the MAIN LOOP

// parameter "address" takes either 's', 'm', or 'h', and sets the data line to that value
void setAddress(char address);


//Transmission helper functions ---------

// Reset function, sets dataline to low, then high
void clearDataline();

// End frame function, pulls dataline to high.
void endFrame();

// End transmission function, pulls dataline to high for 10 clock cycles
void endTransmission();


//Data output function ---------

// writes out time data (using parameters so we only rely on what's given to the function)
void writeOut(char address, int timeData);



// MAIN SETUP
void setup() {

  // Serial terminal setup, only runs if DEBUG isn't nothing
  if(DEBUG != 0){
    Serial.begin(9600);
    while(!Serial);
  }

  // Set timezone offset
  Time.zone(-7);

  //Initialize pins
  pinMode(DATA_LINE, OUTPUT);

  //if using the oscilloscope trigger, set it to low, and indicate we are in debug mode using builtin LED on pin 7
  if(EN_OSC == 1){
    pinMode(SCOPE_TRIGGER, OUTPUT);
    pinMode(DEBUG_INDICATOR, OUTPUT);

    digitalWrite(SCOPE_TRIGGER, LOW);
    digitalWrite(DEBUG_INDICATOR, HIGH);
  }

}

// MAIN LOOP
void loop() {

  //Check if we have new time data, or if the time variables haven't be initialized
  if((seconds == -1 || minutes == -1 || hours == -1) || Time.second() != seconds){

    // Update time variables
    seconds = Time.second();
    minutes = Time.minute();

    (HOUR_FORMAT == 1) ? hours = Time.hour() : hours = Time.hourFormat12();

    // Debug point
    if(DEBUG >= 1) Serial.println("Updated time variables!");

    // Write out the time data
    writeOut('s', seconds);
    writeOut('m', minutes);
    writeOut('h', hours);

  }
}
 
// Function definitions ---------------------------------------------

// parameter "address" takes either 's', 'm', or 'h', and sets the data line to that value
void setAddress(char address){

  // Check that we are given a valid address macro, either 's', 'm', or 'h', errors out if not
  assert(address == 's' || address == 'm' || address == 'h');

  switch (address){
    case 's':
      // In the old code, this was ADDRESS A, or address 001

      digitalWrite(DATA_LINE, LOW);
      delayMicroseconds(CLK_DELAY);

      digitalWrite(DATA_LINE, LOW);
      delayMicroseconds(CLK_DELAY);

      digitalWrite(DATA_LINE, HIGH);
      delayMicroseconds(CLK_DELAY);

      // Debug point
      if(DEBUG == 2) Serial.println("Wrote address A (seconds) to dataline!");

      break;

    case 'm':
      // In the old code, this was ADDRESS B, or address 011

      digitalWrite(DATA_LINE, LOW);
      delayMicroseconds(CLK_DELAY);

      digitalWrite(DATA_LINE, HIGH);
      delayMicroseconds(CLK_DELAY);

      digitalWrite(DATA_LINE, HIGH);
      delayMicroseconds(CLK_DELAY);

      // Debug point
      if(DEBUG == 2) Serial.println("Wrote address B (minutes) to dataline!");

      break;

    case 'h':
      // In the old code, this was ADDRESS C, or address 101

      digitalWrite(DATA_LINE, LOW);
      delayMicroseconds(CLK_DELAY);

      digitalWrite(DATA_LINE, HIGH);
      delayMicroseconds(CLK_DELAY);

      digitalWrite(DATA_LINE, HIGH);
      delayMicroseconds(CLK_DELAY);

      // Debug point
      if(DEBUG == 2) Serial.println("Wrote address C (hours) to dataline!");

      break;
    
    // This case shouldn't happen since the assert statement exists, I just included it by convention
    default:
      break;
  }
}

//Transmission helper functions ---------

// Reset function, sets dataline to low, then high
void clearDataline(){

  digitalWrite(DATA_LINE, LOW);
  delayMicroseconds(CLK_DELAY);
  digitalWrite(DATA_LINE, HIGH);
  delayMicroseconds(CLK_DELAY);

  // Debug point
  if(DEBUG == 2) Serial.println("Dataline cleared!\n");

}

// End frame function, pulls dataline to high.
void endFrame(){

  digitalWrite(DATA_LINE, HIGH);
  delayMicroseconds(CLK_DELAY);

  // Debug point
  if(DEBUG == 2) Serial.println("Data FRAME ended, dataline pulled high!\n");
}

// End transmission function, pulls dataline to high for 10 clock cycles
void endTransmission(){

  digitalWrite(DATA_LINE, HIGH);
  delayMicroseconds(CLK_DELAY*10);

  // Debug point
  if(DEBUG == 2) Serial.println("Data TRANSMISSION ended, dataline pulled high for 10 clock cycles!\n");
}


//Data output function ---------

// writes out time data (using parameters so we only rely on what's given to the function)
void writeOut(char address, int timeData){

  // Check that we are given a valid address macro, either 's', 'm', or 'h', errors out if not
  assert(address == 's' || address == 'm' || address == 'h');

  //Set up array of split place values
  int splitNumber[2];
  splitNumber[1] = timeData % 10;
  splitNumber[0] = timeData / 10;

  /* This next block of code replaces the following block structure:
      Reset();                    //FIRST FRAME Seconds/Minutes/Hours
      SetAddressA/B/C();
      FirstFrameSeconds/Minutes/Hours();
      EndFrame();
      //digitalWrite(11,HIGH);
      
      //digitalWrite(11,LOW);
      Reset();                    //SECOND FRAME Seconds/Minutes/Hours
      SetAddressA/B/C();
      SecondFrameSeconds/Minutes/Hours();
      EndTransmission();
      //digitalWrite(11,HIGH);
  */

  //Loop to send out data for both place values to the desired chip
  //p being the index or "place value" in our splitNumber array
  for(int p = 1; p > -1; p--){

    if(EN_OSC == 1) digitalWrite(SCOPE_TRIGGER, HIGH);               //Set oscilloscope trigger to high while we do a transmission

    //Prepare data line for transmitting the ones data to desired chip
    clearDataline();
    setAddress(address); 

    //iterate through ones variable and write out the bits to the data line
    for (int i = 0; i < 4; i++){

      // Ternary statement which essentially maps the dataline's value to the ones variable
      (splitNumber[p] & 1) ? digitalWrite(DATA_LINE, HIGH) : digitalWrite(DATA_LINE, LOW);
      delayMicroseconds(CLK_DELAY);

      // Debug point
      if(DEBUG == 2) Serial.println("Wrote data to dataline!");

      splitNumber[p] = splitNumber[p] >> 1;
    }

    endFrame();

    if(EN_OSC == 1 && p == 0) digitalWrite(SCOPE_TRIGGER, LOW);               //drop trigger to low when done with transmission, ignoring when we need to do an end transmission
  }
  
  // Now that we're done sending data, end the transmission
  endTransmission();

  if(EN_OSC == 1) digitalWrite(SCOPE_TRIGGER, HIGH);               //drop trigger to low when completely done with data transfer
}
