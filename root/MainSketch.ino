//Importing classes setup by ASCEND Programming to abstract default libraries 
//Every class supports: setPin(), verifyPin(), readData()/writeData() to interface with input sensors and output peripherals such as the SD Card
#include "Sensor.h"
#include "TMP36-Sensor.h"
#include "BME680-Sensor.h"
#include "SHT31-Sensor.h"
#include "LSM9DS1-Sensor.h"
#include "SGP30-Sensor.h"
#include "INA260-Sensor.h"
#include "SDCard.h"

#Create class objects
// MISO MOSI CS TX RX
TMP36-Sensor tmp36 = new TMP36-Sensor();
BME680-Sensor bme680 = new BME680-Sensor();
SHT31-Sensor sht31 = new SHT31-Sensor();
LSM9DS1-Sensor lsm9ds1 = new LSM9DS1-Sensor();
SGP30-Sensor sgp30 = new SGP30-Sensor();
INA260-Sensor ina260 = new INA260-Sensor();
SDCard sd = new SDCard();

// Create an array of Sensor pointers
Sensor* sensors[] = {&tmp36, &bme680, &sht31, &lsm9ds1, &sgp30, &ina260};
// Create a global int for Size of sensors[]
const int numSensors = sizeof(sensors) / sizeof(sensors[0]);

void setup(){
  // Call verifyPin() to check status of successful sensor communication
    if (verifyPin()) {
        Serial.println("Moving on. At least one sensor has successful communication.");
    } else {
        Serial.println("Stopping Execution. All sensor communications failed.");
    }
  //verify comms with SD Card
  if (sd->verifyPin()) {
   Serial.println("Moving on. SD card has successful communication");
  }
  Serial.println("Stopping Execution. SD card communication failed");
  //Initialise CSV header to SD card
  //.
  //.
  //.
}
void loop(){
  //Writes data into SD Card if communication with SD Card and at least one SD Card is successful
  writeData();
}
bool verifyPin() {
  //Create an array for PinVerification
  bool pinVerificationResults[numSensors];
  for (int i = 0; i < numSensors; i++){
    pinVerificationResults[i] = sensors[i]->verifyPin();
  }
  Serial.println("Pin Verification Results:");
  for (int i = 0; i < numSensors; i++){
    Serial.print(sensors[i]->getSensorName());
    Serial.print(": ");
    Serial.println(pinVerificationResults[i] ? "Successful in Communication" : "Failure in Communication (check wirings and/ or pin definitions in the respective sensor header file)");
  }
  Serial.println();
  for (int i = 0; i < numSensors; ++i) {
        if (pinVerificationResults[i]) {   
          return true;  // At least one pin verification passed
        }
    }
    return false; // All pin verification failed
}
bool writeData(){
  //.
  //.
  //.
  return false;
}
