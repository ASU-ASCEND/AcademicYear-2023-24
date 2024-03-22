#include <Wire.h>
#include <Arduino_LSM9DS1.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Adafruit_SGP30.h"
#include "Adafruit_SHT31.h" // Add this line for the SHT31-D sensor
#include <Adafruit_GPS.h>
#include <SPI.h>
#include <SD.h>

//PIN 12 Internal LED
//const int internalPIN = 12; // Pin number where the LED is connected

//PIN 13 Internal LED
//const int externalPin = 13; // Pin number where the LED is connected

//PIN 30 Raw Battery Voltage
//const int voltagePin = 30;  // Pin number where the voltage is measured
//float rawVoltage;

//LSM9DS1 initialization
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

//GPS Variables
// Define GPS RX and TX pins
#define GPS_RX 2
#define GPS_TX 1
#define GPSECHO false
uint32_t timer = millis(); // Time

Adafruit_GPS GPS(&Wire); // Create GPS object


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

const int geigerPin = 4; // Geiger counter connected to digital pin 6
volatile unsigned long pulseCount = 0;
unsigned long previousMillis = 0;
const long interval = 1000;  // Interval for CPS calculation (1 second)
const float conversionFactor = 0.00812; // Conversion factor to uSv/h (micro-Sieverts/hour)

Adafruit_BME680 bme;  // BME680 sensor
Adafruit_SGP30 sgp;   // SGP30 sensor
Adafruit_SHT31 sht31; // SHT31-D sensor

const int tmp36pin_int = 1; // TMP36 analog temperature sensor
const int tmp36pin_ext = 0; //TMP36 analog temperature sensor
const int chipSelect = 11; // SD card chip select pin -> D7

bool enableHeater = true;
uint8_t loopCnt = 0;

File dataFile; //CSV for Sensor Data

void countPulse() {
  pulseCount++;
}

/*void blinkLED(int delayTime) {
  digitalWrite(externalPin, HIGH);  // Turn on the LED
  delay(delayTime);  // Wait for the specified delay time
  digitalWrite(externalPin, LOW);  // Turn off the LED
  delay(delayTime);  // Wait for the specified delay time
}*/

void setup() {
  Serial.begin(9600);

  //pinMode(externalPin, OUTPUT);  // Set the LED pin as an output
  //pinMode(voltagePin, INPUT);  // Set the voltage pin as an input

  //digitalWrite(externalPin, HIGH);// Custom led high forced

  //GPS Setup
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  //delay(1000);
  GPS.println(PMTK_Q_RELEASE);
  Serial.println("GPS Initialized.");

  pinMode(geigerPin, INPUT_PULLUP);  // Enable internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(geigerPin), countPulse, FALLING); // Count pulses on falling edge

  
  //while (!Serial) { delay(50); } // Wait for serial console to open!

  Serial.println("Sensor Fusion Test");

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    //while (1);
  }

  if (!sgp.begin()){
    Serial.println("Could not find a valid SGP30 sensor, check wiring!");
    //while (1);
  }

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    //while (1);
  }

  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

  // Set up oversampling and filter initialization for BME680
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  // Initialize SHT31-D sensor
  if (!sht31.begin(0x44)) {   // Set to 0x45 for alternate I2C address
    Serial.println("Couldn't find SHT31");
    //while (1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");

  // Initialize TMP36 sensors
  pinMode(tmp36pin_int, INPUT);
  pinMode(tmp36pin_ext, INPUT);

  //LSM9DS1 Setup
  if(!lsm.begin()){
    /*There was a problem detecting the LSM9DS1... check your connections*/
    Serial.print("no LSM9DS1 detected...check your wiring!");
  }
  //LSM9DS1 Ranges
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
  
  Serial.print("Initializing SD card...");
  delay(2000);  // Added delay before SD card initialization
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    //while (1);
  }
  Serial.println("card initialized.");
  
  // Open the file for data logging
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("error opening datalog.csv");
  } else {
    // Add a header row with sensor names
    dataFile.println("Time, Temperature (TMP36-Internal (short cable)), External Temperature (TMP36-External) (long cable), External Temperature (SHT30) (˚C), External Humidity (SHT30) (˚C), Temperature (BME680),Pressure (hPa),Altitude (m),Humidity (%),Gas Resistance (KOhms),TVOC (ppb),eCO2 (ppm),Acceleration (X),Acceleration (Y),Acceleration (Z),Acceleration_SensorEvent (LSM9DS1) (X) (g's),Acceleration_SensorEvent (LSM9DS1) (Y) (g's),Acceleration_SensorEvent (LSM9DS1) (Z) (g's), Magnetometer_SensorEvent (LSM9DS1) (X) (g's), Magnetometer_SensorEvent (LSM9DS1) (Y) (g's), Magnetometer_SensorEvent (LSM9DS1) (Z) (g's),Gyroscope_SensorEvent (LSM9DS1) (X) (g's),Gyroscope_SensorEvent (LSM9DS1) (Y) (g's),Gyroscope_SensorEvent (LSM9DS1) (Z) (g's), Counts Per Second (CPS), Radiation Level (Geiger)(mSv), Latitude (GPS), Longitude (GPS), Speed (GPS)(knots), Altitude (meters)");
  }
}


int counter = 0;
void loop() {

  float temperature_int;  // Declare temperature_int here

  //float rawValue = analogRead(voltagePin);  // Read the analog voltage value
  //rawVoltage = (rawValue / 1023.0) * 3.3;

  // Check if the voltage is below a certain threshold (adjust this value based on your setup)
  /*if (rawVoltage < 2.44) {
    // Power disruption detected
    blinkLED(100);  // Blink slower (2 seconds ON, 2 seconds OFF)
  } else {
    // Normal power
    blinkLED(100);  // Default blink rate (0.5 seconds ON, 0.5 seconds OFF)
  }*/

  //LSM9DS1 variables
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);
  float x_event = accel.acceleration.x;
  float y_event = accel.acceleration.y;
  float z_event = accel.acceleration.z;
  // Read data from the GPS
  char c = GPS.read();
  if (GPSECHO && c)
    if (c) Serial.print(c);

  // Check if a new NMEA sentence is received
  if (GPS.newNMEAreceived()) {
    Serial.println(GPS.lastNMEA());
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  // Read data from the BME680 sensor
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading from BME680 :(");
    return;
  }

  // Read data from the SGP30 sensor
  if (!sgp.IAQmeasure()) {
    Serial.println("Measurement from SGP30 failed");
    return;
  }

  // Read data from the SHT31-D sensor
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (!isnan(t)) {
    Serial.print("SHT31 - Temp *C = "); Serial.print(t); Serial.print("\t\t");
  } else {
    Serial.println("Failed to read SHT31 temperature");
  }

  if (!isnan(h)) {
    Serial.print("SHT31 - Hum. % = "); Serial.println(h);
  } else {
    Serial.println("Failed to read SHT31 humidity");
  }

  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }

  int reading_ext = analogRead(tmp36pin_ext);
  float voltage_ext = reading_ext * (3.3 / 1024.0);
  float temperature_ext = (voltage_ext - 0.5) * 100;

  int reading_int = analogRead(tmp36pin_int);
  float voltage_int = reading_int * (3.3/ 1024.0);
  temperature_int = (voltage_int - 0.5) * 100;
  
  Serial.print("TMP36 - Temperature = ");
  Serial.print(temperature_int);
  Serial.println(" *C");

  Serial.print("TMP36 - External Temperature = ");
  Serial.print(temperature_ext);
  Serial.println(" *C");

  Serial.print("SHT30 (˚C) - External Temperature = ");
  Serial.println(t);
  Serial.print("SHT30 (%) - External Humidity");
  Serial.println(h);

  Serial.print("BME688 - Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("BME688 - Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print("BME688 - Altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");

  Serial.print("BME688 - Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("BME688 - Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("SGP30 - TVOC (ppb) = "); 
  Serial.println(sgp.TVOC); 
  Serial.print("\t eCO2 (ppm) = "); 
  Serial.println(sgp.eCO2);

  Serial.print("LSM9DS1 - Acceleration (g's) - X: "); 
  Serial.print(x);
  Serial.print(" Y: "); 
  Serial.print(y);
  Serial.print(" Z: "); 
  Serial.println(z);

  //Reads Geiger Counter approximately every 1 second
  //unsigned long currentMillis = millis();
  unsigned long cps;
  float radiationLevel;

  if (millis() - timer > 1000) {
    timer = millis();

    noInterrupts(); // Disable interrupts to get a stable pulse count
    cps = pulseCount;
    pulseCount = 0;  // Reset pulse count
    interrupts();    // Re-enable interrupts

    radiationLevel = cps * conversionFactor; // Convert to uSv

    // Print the data 
    Serial.print("CPS: ");
    Serial.print(cps);
    Serial.print(", Radiation Level (mSv): ");
    Serial.println(radiationLevel);
  }
    //GPS Serial
    Serial.print("Latitude: ");
    Serial.println(GPS.latitudeDegrees);
    Serial.print("Longitude: ");
    Serial.println(GPS.longitudeDegrees);
    Serial.print("Speed (knots): ");
    Serial.println(GPS.speed);
    Serial.print("Altitude (meters): ");
    Serial.println(GPS.altitude);
    Serial.println("-----------------------------------------------------");

    //String dataString = String(cps)+ ","+ String(radiationLevel);
  
    /*// Write sensor data to the SD card
    dataFile1 = SD.open("datalogGeiger.csv", FILE_WRITE);
  if (dataFile1) {
    Serial.println("I'm Here!!");
    dataFile1.println(dataString1);
    dataFile1.flush(); // Ensure data is written immediately
    Serial.println(dataString1);
    dataFile1.close();
  } else {
    Serial.println(" error writing to datalogGeiger.csv");
  }*/

    // You can call our function to write data to the SD card here
    //writeDataToSDCard(cps, radiationLevel);

  // Create a string for sensor data with labels and units
  String dataString = "Time (GPS) (Hours:Minute:Second:Millisecond):" + String(GPS.hour)+":"+String(GPS.minute)+":"+String(GPS.seconds)+":"+String(GPS.milliseconds)+","+
                      "Temperature (TMP36int) (°C): " + String(temperature_int) + "," +
                      "Temperature (TMP36ext) (˚C): " + String(temperature_ext) + "," +
                      "External Temperature (SHT30) (˚C): " + String(t) + "," +
                      "External Humidity (SHT30) (˚C): " + String(h) + "," +
                      "Temperature (BME680) (°C): " + String(bme.temperature) + "," +
                     "Pressure (BME680) (hPa): " + String(bme.pressure / 100.0) + "," +
                     "Altitude (BME680) (m): " + String(altitude) + "," +
                     "Humidity (BME680) (%): " + String(bme.humidity) + "," +
                     "Gas Resistance (BME680) (KOhms): " + String(bme.gas_resistance / 1000.0) + "," +
                     "TVOC (SGP30) (ppb): " + String(sgp.TVOC) + "," +
                     "eCO2 (SGP30) (ppm): " + String(sgp.eCO2) + "," +
                     "Acceleration (LSM9DS1) (X) (g's): " + String(x) + "," +
                     "Acceleration (LSM9DS1) (Y) (g's): " + String(y) + "," +
                     "Acceleration (LSM9DS1) (Z) (g's): " + String(z) + "," + 
                     "Acceleration_SensorEvent (LSM9DS1) (X) (g's): " + String(x_event) + "," +
                     "Acceleration_SensorEvent (LSM9DS1) (Y) (g's): " + String(y_event) + "," +
                     "Acceleration_SensorEvent (LSM9DS1) (Z) (g's): " + String(z_event) + "," +
                     "Magnetometer_SensorEvent (LSM9DS1) (X) (g's): " + String(mag.magnetic.x) + "," +
                     "Magnetometer_SensorEvent (LSM9DS1) (Y) (g's): " + String(mag.magnetic.y) + "," +
                     "Magnetometer_SensorEvent (LSM9DS1) (Z) (g's): " + String(mag.magnetic.z) + "," +
                     "Gyroscope_SensorEvent (LSM9DS1) (X) (g's): " + String(gyro.gyro.x) + "," +
                     "Gyroscope_SensorEvent (LSM9DS1) (Y) (g's): " + String(gyro.gyro.y) + "," +
                     "Gyroscope_SensorEvent (LSM9DS1) (Z) (g's): " + String(gyro.gyro.z) + "," +
                     "Counts Per Second (Geiger): "+ String(cps) + "," +
                     "Radiation Level (Geiger) (mSv):"+ String(radiationLevel) + "," +
                     "Latitude: " + String(GPS.latitudeDegrees) + 
                   ", Longitude: " + String(GPS.longitudeDegrees) +
                   ", Speed (knots): " + String(GPS.speed) +
                   ", Altitude (meters): " + String(GPS.altitude);

  // Write sensor data to the SD card
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.flush(); // Ensure data is written immediately
    Serial.println(dataString);
  } else {
    Serial.println("error writing to datalog.csv");
  }

  //delay(2000);

  counter++;
  if (counter == 30) {
    counter = 0;
    uint16_t TVOC_base, eCO2_base;
    if (!sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get SGP30 baseline readings");
      return;
    }
    Serial.print("****SGP30 Baseline values: eCO2: 0x"); 
    Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x"); 
    Serial.println(TVOC_base, HEX);
  }
}
