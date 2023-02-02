#include "TFRDataAq.h"

void accel_setup(){
  lis.setRange(LIS3DH_RANGE_4_G);   //Range is set to 4g
 if (! lis.begin(0x18)) { // change this to 0x19 for alternative i2c address
  //Serial.println("Couldnt start");
  while (1);
 }
}

// Accelerometer functions for x y and Z
//
float accelX() {
  //An object of type even is created 
  //
  sensors_event_t event;
  //Getting data from that object's memory address
  //
  lis.getEvent(&event);
  //Serial.print(event.acceleration.x);
  //event.acceleration.x is class data
  //
  return event.acceleration.x;
}

float accelY() {
  sensors_event_t event;
  lis.getEvent(&event);
  //Serial.print(event.acceleration.y);
  return event.acceleration.y;
}

float accelZ() {
  sensors_event_t event;
  lis.getEvent(&event);
  //Serial.print(event.acceleration.z);
  return event.acceleration.z;
}

//Function to get the angle of the steering wheel
//
float getSteeringAngle() {
  float steeringInput = analogRead(A1);  //Read along input from pin A1, adjust it and offset it
  steeringInput = (map(steeringInput , 45 , 1023 , -18000 , 18000)) / 100;  //Map the steering angle to values between -180 to 180
  //Serial.print(steeringInput);  //Print Value read, change the 200 value to fine tune value for 0
  //Serial.print(" ");
  return(steeringInput);
}

float temp() {
  //Define the analog pin to read the thermistor
  //
  int ThermPin = A2;
  float Vo = analogRead(ThermPin);
  //Convert the analogvalue to a temp value that we can use
  //
  float T = (1023/Vo)-1;
  T = (R/T)/4.17;
  //Serial.print(" ");
  //Serial.print(T);
  //Serial.println(" C");
  return(T);
}

float LVDT(){
  //Read the value from analog pin 3
  //
  float sensorValue = analogRead(A3);
  
  //Adjust to the displacement of the LVDT
  //
  float displacement=47.91*sensorValue;
  //Serial.print(" ");
  //Serial.println(displacement);
  return(displacement);
       // delay in between reads for stability
}


//Function to initialize the SD card and make sure the serial is working and connected
//
void SDinitialize(){
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  //see if the card is present and can be initialized:
  //if the card isn't properly connected, we stop
  SD.begin();
  if (!SD.begin()) {
    Serial.println("Card failed, or not present");
    while (1);     // don't do anything more
  }
  
  //Done initializing
  //
  Serial.println("card initialized.");

  Serial.println("naming file...");
  #define FILE_BASE_NAME "DataAq"

  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  fileName = FILE_BASE_NAME "00.txt";


    while (SD.exists(fileName)) {
      if (fileName[BASE_NAME_SIZE + 1] != '9') {
        fileName[BASE_NAME_SIZE + 1]++;
      } 
      else if (fileName[BASE_NAME_SIZE] != '9') {
        fileName[BASE_NAME_SIZE + 1] = '0';
        fileName[BASE_NAME_SIZE]++;
      } 
      else {
        Serial.println(F("Can't create file name"));
        return;
    }
  }
  file = SD.open(fileName, FILE_WRITE);
  if (!file) {
    Serial.println(F("open failed"));
    return;
  }
  Serial.print(F("opened: "));
  Serial.println(fileName);
}

//Function to log data to the SD card
//

void SDlog(){
  //Open a file pointer
  //
  file = SD.open(fileName, FILE_WRITE);
  
  //Declare a data array
  //
  float DataArray[6] = {accelX(), accelY(), accelZ(), getSteeringAngle(), temp(), LVDT()};
  
  //Error handling for file open failure
  //
  if (!file) {
    Serial.print(F(" open failed"));
    return;
  }
  //Display opened file and its name
  //
  Serial.print(F("opened: "));
  Serial.print(fileName);

  //Print a timestamp for the data
  //
  file.print(millis());
  file.print(": ");

  //Index through the array and print each element
  //
  for(int i = 0 ; i < sizeof(DataArray) ; i++){
    file.print(DataArray[i]);
    file.print(" ");
  }
  //Print a newline character
  //
  file.println();
  //Close the file
  //
  file.close();
} 