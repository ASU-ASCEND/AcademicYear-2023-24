//Importing classes setup by ASCEND Programming to abstract default libraries 
//Every class supports: setPin(), verifyPin(), readData()/writeData() to interface with input sensors and output peripherals such as the SD Card
#include "Sensor.h"
#include "TMP36Sensor.h"
#include "BME680Sensor.h"
#include "SHT31Sensor.h"
#include "LSM9DS1Sensor.h"
#include "SGP30Sensor.h"
#include "INA260Sensor.h"
#include "MTK3339Sensor.h"
#include "AnalogSensor.h"
//#include "GeigerSensor.h"
#include "GeigerSlowSensor.h"
#include "ZOPT220Sensor.h"
#include "LSM6DSOXSensor.h"

#include "SDCard.h"


//Create class objects
// MISO MOSI CS TX RX
TMP36Sensor* tmp36 = new TMP36Sensor();
BME680Sensor* bme680 = new BME680Sensor();
SHT31Sensor* sht31 = new SHT31Sensor();
LSM9DS1Sensor* lsm9ds1 = new LSM9DS1Sensor();
LSM6DSOXSensor* lsm6dsox = new LSM6DSOXSensor();
SGP30Sensor* sgp30 = new SGP30Sensor();
INA260Sensor* ina260 = new INA260Sensor();
MTK3339Sensor* mtk3339 = new MTK3339Sensor();
AnalogSensor* analog = new AnalogSensor();
//GeigerSensor* geiger = new GeigerSensor();
GeigerSlowSensor* geigerSlow = new GeigerSlowSensor();
ZOPT220Sensor* uv = new ZOPT220Sensor();
SDCard* sd = new SDCard();

// declaration
bool verifyPin();
void writeData();

// Create an array of Sensor pointers
Sensor* sensors[] = {tmp36, bme680, sht31, lsm9ds1, lsm6dsox, sgp30, ina260, mtk3339, analog, uv, geigerSlow};
// Create a global int for Size of sensors[]
const int numSensors = sizeof(sensors) / sizeof(sensors[0]);
bool pinVerificationResults[numSensors];

void setup(){
  Serial.begin(9600);
  delay(10000);
  // Call verifyPin() to check status of successful sensor communication
  if (verifyPin()) {
      Serial.println("Moving on. At least one sensor has successful communication.");
  } else {
      Serial.println("Stopping Execution. All sensor communications failed.");
  }
  // //verify comms with SD Card
  if (sd->verifyPin()) {
   Serial.println("Moving on. SD card has successful communication");
  }
  else {
    Serial.println("SD card communication failed");
  }
  // //Initialise CSV header to SD card
  String header = "Millis, ";

  for(int i = 0; i < numSensors; i++){
    if(pinVerificationResults[i]){
      header += sensors[i]->getSensorCSVHeader();
    }
  }
  header += "\n";
  Serial.println(header);
  // //sd->writeData(header);
  delay(1000);
}
bool ledVal = 0;
void loop(){
  delay(10);
  //Writes data into SD Card if communication with SD Card and at least one SD Card is successful
  writeData();
  digitalWrite(LED_BUILTIN, ledVal);
  ledVal = !ledVal;
}

bool verifyPin() {
  //Create an array for PinVerification
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

void writeData(){
  String output = String(millis()) + ", ";

  for(int i = 0; i < numSensors; i++){
    if(pinVerificationResults[i]){
      output += sensors[i]->readData();
    }
  }

  output += "\n";

  Serial.print(output);

  //sd->writeData(output);
}
