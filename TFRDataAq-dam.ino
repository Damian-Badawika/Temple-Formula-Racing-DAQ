//Local include files
//
#include "TFRDataAq.h"

//TFR Data Acquisition: The Damian Badawika Experience
//
void setup() {
  //Initialize serial baud rate to 9600
  //
  Serial.begin(9600);
  //Initialize sd card logger
  //
  SDinitialize();
  accel_setup();
}

void loop() {
  //Call functions for each sensor
  //
  // accelerometer();
  getSteeringAngle();
  temp();
  accelX();
  LVDT();
  accelY();
  accelZ();
  Serial.println();
  SDlog();
  delay(100);
}
