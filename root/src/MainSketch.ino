//Importing classes setup by ASCEND Programming to abstract default libraries 
//Every class supports: setPin(), verifyPin(), readData()/writeData() to interface with input sensors and output peripherals such as the SD Card

#include <Arduino.h> // Include the Arduino library
#include "Sensor.h"
#include "TMP36Sensor.h"
#include "BME680Sensor.h"
#include "SHT31Sensor.h"
#include "LSM9DS1Sensor.h"
#include "SGP30Sensor.h"
#include "INA260Sensor.h"
#include "MTK3339Sensor.h"
#include "AnalogSensor.h"
#include "ZOPT220Sensor.h"
#include "LSM6DSOXSensor.h"
#include "WiFiNINA.h"
#include "GeigerSensor.h"

#include <Arduino.h>

#define PIN_SD_MOSI       PIN_SPI_MOSI
#define PIN_SD_MISO       PIN_SPI_MISO
#define PIN_SD_SCK        PIN_SPI_SCK
#define PIN_SD_SS         PIN_SPI_SS

#define _RP2040_SD_LOGLEVEL_       4

#include <SPI.h>
#include <RP2040_SD.h>

#define SD_CHIP_SELECT 7

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
GeigerSensor* geiger = new GeigerSensor();
ZOPT220Sensor* uv = new ZOPT220Sensor();

#define DEFAULT_CLASSES 4

#define LED_PIN 9
#define STATUS_PIN 10

// declaration
//bool verifyPin();
void writeData();

// Create an array of Sensor pointers
Sensor* sensors[] = {bme680, sht31, lsm9ds1, lsm6dsox, sgp30, ina260, mtk3339, analog, uv, geiger}; 
// Create a global int for Size of sensors[]
const int numSensors = sizeof(sensors) / sizeof(sensors[0]);
bool pinVerificationResults[numSensors];

File myFile;
String fileName; 

#define INDICATION_PERIOD 1000
int lastIndication = 0;

bool noContinuity = false;
bool noPins = false;
bool noFile = false;

int ledVal = LOW;
int statusVal = LOW;
int rgbVal = LOW; 


// b - no sd recognized, g - no sensors plugged in, r - no file can be written

// specify 'r' 'g' or 'b' to set that color, anything else to turn it off
void setRGBLED(char color, int val){
  digitalWrite(LEDR, ((color == 'r' && val)? HIGH : LOW));
  digitalWrite(LEDG, ((color == 'g' && val)? HIGH : LOW));
  digitalWrite(LEDB, ((color == 'b' && val)? HIGH : LOW));
}


void setup(){
  
  bme680->setPeriod(    2000); // in ms
  sht31->setPeriod(     2000);
  lsm9ds1->setPeriod(   0); 
  lsm6dsox->setPeriod(  2000);
  sgp30->setPeriod(     2000);
  ina260->setPeriod(    2000);
  mtk3339->setPeriod(   2000);
  analog->setPeriod(    2000);
  // geigerSlow->setPeriod(2000);
  geiger->setPeriod(2000);
  uv->setPeriod(        2000);

  //WiFi Nina color LED stuff
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  setRGBLED('n', rgbVal);
  // internal LED - blinks with main
  pinMode(LED_PIN, OUTPUT);
  // status LED - external - on to mean all good 
  pinMode(STATUS_PIN, OUTPUT);
  digitalWrite(STATUS_PIN, HIGH);
  Serial.begin(115200);
  delay(5000);
  // Call verifyPin() to check status of successful sensor communication
  if (verifyPin()) {
      Serial.println("Moving on. At least one sensor has successful communication.");
  } else {
      Serial.println("Stopping Execution. All sensor communications failed.");
  }

  while(!SD.begin(SD_CHIP_SELECT)){
    Serial.println("SD Card not working");
    // status pin
    statusVal = !statusVal;
    digitalWrite(STATUS_PIN, statusVal);
    rgbVal = !rgbVal;
    setRGBLED('b', rgbVal);
    delay(600);
  }
  statusVal = HIGH;
  setRGBLED('n', rgbVal);
  Serial.println("SD Card Working"); 

  fileName = "data.csv";

  for (int i = 0; i < 1000; i++) {
    fileName = "d" + String(i) + ".csv";
    if (!SD.exists(fileName)) {
        if(i > 0) noContinuity = true;
        // Name the file for writing
        Serial.println("Opened new file: " + fileName);
        break;
    }
  }

  String data = "Testing writing tp " + fileName; // was char data[] = 

  myFile = SD.open(fileName, FILE_WRITE);

  if(myFile){
    myFile.println(data);
    myFile.close();
    Serial.println("done.");
    noFile = false;
  }
  else {
    Serial.println("Can't write setup 1");
    noFile = true;
  }


  myFile = SD.open(fileName, FILE_READ);

  if(myFile){
    while(myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
    Serial.println("\nDone.");
    noFile = false;
  }
  else {
    Serial.println("Can't read setup");
    noFile = true; 
  }

  // //Initialise CSV header to SD card
  String header = "Millis, ";
  for(int i = 0; i < numSensors; i++){
    if(pinVerificationResults[i]){
      header += sensors[i]->getSensorCSVHeader();
    }
  }

  Serial.println(header);

  myFile = SD.open(fileName, FILE_WRITE);

  if(myFile){
    myFile.println(header);
    myFile.close();
    Serial.println("done.");
    noFile = true;
  }
  else {
    Serial.println("Error opening setup");
    noFile = false;
  }

}

int it = 0;
void loop(){
  it++;
  Serial.println("it: " + String(it));
  delay(100);

  // build csv row
  String ourData = String(millis()) + ", "; 
  int now = millis();
  
  for(int i = 0; i < numSensors; i++){
    if(pinVerificationResults[i]){
      if((now - sensors[i]->getLastExecution()) > sensors[i]->getPeriod()){
        ourData += sensors[i]->readData();
      }
      else {
        ourData += sensors[i]->readEmpty();
      }
    }
  }
  int after = millis();
  for(int i = 0; i < numSensors; i++){
    if(pinVerificationResults[i]){
      if((now - sensors[i]->getLastExecution()) > sensors[i]->getPeriod()){
        sensors[i]->setLastExecution(after);
      }
    }
  }

  // print csv row
  Serial.println(ourData);

  // save csv row to SD card
  myFile = SD.open(fileName, FILE_WRITE);

  if(myFile){
    myFile.println(ourData);
    myFile.close();
    Serial.println("done.");
    noFile = false;
  }
  else {
    Serial.println("Can't write loop");
    noFile = true;
  }

  // blink indicators for errors
  // EXTERNAL INDICATOR
  // any internal error 
  if(millis() - lastIndication > INDICATION_PERIOD){
    lastIndication = millis();
    if(noPins || noFile){
      for(int i = 0; i < 1*2; i++){
        statusVal = !statusVal;
        digitalWrite(STATUS_PIN, statusVal);
        delay(100);
      }
    }
    else if(noContinuity){
      for(int i = 0; i < 2*2; i++){
        statusVal = !statusVal;
        digitalWrite(STATUS_PIN, statusVal);
        delay(100);
      }
    }
    else {
      for(int i = 0; i < 3*2; i++){
        statusVal = !statusVal;
        digitalWrite(STATUS_PIN, statusVal);
        delay(100);
      }
    }
    digitalWrite(STATUS_PIN, HIGH);
  }
  
  // PCB INDICATOR
  digitalWrite(LED_PIN, ledVal);
  ledVal = !ledVal;
  // if no continuity then blink statusVal with main
  // COLOR INDICATOR
  if(noFile){
    rgbVal = !rgbVal;
    setRGBLED('r', rgbVal);
  }
  else if(noPins){
    rgbVal = !rgbVal;
    setRGBLED('g', rgbVal);
  }
  // delay(500);
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

  int count = 0; 
  for (int i = 0; i < numSensors; ++i) {
      if (pinVerificationResults[i]) {   
        count++; 
      }
  }
  noPins = count <= DEFAULT_CLASSES;
  return count != 0;  // At least one pin verification passed
}

void writeData(){
  String output = String(millis()) + ", ";

  Serial.println(output);

  myFile = SD.open(fileName, FILE_WRITE);

  if(myFile){
    myFile.println("data");
    myFile.close();
    Serial.println("done.");
  }
  else {
    Serial.println("Error opening");
  }


  myFile = SD.open(fileName, FILE_READ);

  if(myFile){
    while(myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
    Serial.println("\nDone.");
  }
  else {
    Serial.println("Can't write");
  }

}
