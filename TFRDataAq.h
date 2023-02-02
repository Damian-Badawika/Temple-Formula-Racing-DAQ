//Make all definitions once
//
#ifndef TFRDataAq
#define TFRDataAq

//Include a bunch of libraries we need
//
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

//R is a value we need to calculate the temperature from the resistor
//
#define R 1000

//Declare a global variable for the file to log the data to and the
//Array of the data values
File file;

//Define the accelerometer sensor
//
//Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
#if defined(ARDUINO_ARCH_SAMD)
  #define Serial SerialUSB
#endif

const int chipSelect = 10;//Define a variable for the SD card
//
String nameString = "";
char* fileName = ""; 
//Read along input from pin A1, adjust it and offset it
//

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the 
Zero!
  #define Serial SerialUSB
#endif

//Define all of our handy dandy functions
//Setup funcs
//
void SDinitialize();
void accel_setup();

//Data funcs
float accelX();
float accelZ();
float accelY();
float getSteeringAngle();
float temp();
float LVDT();
void SDlog();

#endif
