/***************************************************************************
  Title: StratoDevils_Components_Code_V6.0
  Name(s): Muhammed Topiwala
  Date: 11-15-22
  Description: 
  V6.0 
  This code was constructed mainly using basic example code and StratoDevil's previous
  launch code. The sensors used are: TMP36 (Temperature), mpu6050 (Accelerometer & Gyro), MPRLS (Pressure), 
  amazon spi microsd card (mircoSD Card), SEN54(VOC)

  V6.1 Muhammed Topiwala
  Making final edits in initialization to ensure operation on PCB

  v4.3 Feras Jayyusi, Sagan Richardson
  Updated header to reflect changes and shortned names. (DO NOT CHANGE Latitude and Longitude header names. Needed for Elevation calculation script post-flight.
  
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_SGP30.h>
#include <Adafruit_LSM9DS1.h>
#include <SD.h>
#include <TinyGPS++.h>

// Create sensor objects
Adafruit_BME680 bme;
Adafruit_SHT31 sht;
Adafruit_LSM9DS1 lsm;
Adafruit_SGP30 sgp;
TinyGPSPlus gps;

const int chipSelect = 10; // SD Card CS pin
File dataFile;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize sensors
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  if (!sht.begin(0x44)) {
    Serial.println("Could not find a valid SHT30 sensor, check wiring!");
    while (1);
  }

  if (!lsm.begin()) {
    Serial.println("Could not find a valid LSM9DS1 sensor, check wiring!");
    while (1);
  }

  if (!sgp.begin()) {
    Serial.println("Could not find a valid SGP30 sensor, check wiring!");
    while (1);
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }

  // Open or create a file to write data
  dataFile = SD.open("sensor_data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error opening sensor_data.csv");
    while (1);
  }

  // Write header to CSV file
  dataFile.println("Temperature_BME,Pressure_BME,Humidity_BME,Gas_BME,Temperature_SHT,Humidity_SHT,Accel_X,Accel_Y,Accel_Z,Mag_X,Mag_Y,Mag_Z,Gyro_X,Gyro_Y,Gyro_Z,CO2_SGP,TVOC_SGP,Latitude,Longitude,Altitude,Date,Time");

  // Close the file
  dataFile.close();
}

void loop() {
  // Read and print data from each sensor
  readBME680();
  readSHT30();
  readLSM9DS1();
  readSGP30();
  readGPS();

  // Open the file in append mode
  dataFile = SD.open("sensor_data.csv", FILE_WRITE);

  // Append data to CSV file
  if (dataFile) {
    dataFile.print(bme.temperature);
    dataFile.print(",");
    dataFile.print(bme.pressure / 100.0);
    dataFile.print(",");
    dataFile.print(bme.humidity);
    dataFile.print(",");
    dataFile.print(bme.gas_resistance / 1000.0);
    dataFile.print(",");
    dataFile.print(sht.readTemperature());
    dataFile.print(",");
    dataFile.print(sht.readHumidity());
    dataFile.print(",");
    readLSM9DS1ToSD();
    readSGP30ToSD();
    readGPSToSD();
    dataFile.println();

    // Close the file
    dataFile.close();
  } else {
    Serial.println("Error opening sensor_data.csv for writing");
  }

  delay(1000); // Delay for 1 second between readings
}

void readLSM9DS1ToSD() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  dataFile.print(accel.acceleration.x);
  dataFile.print(",");
  dataFile.print(accel.acceleration.y);
  dataFile.print(",");
  dataFile.print(accel.acceleration.z);
  dataFile.print(",");
  dataFile.print(mag.magnetic.x);
  dataFile.print(",");
  dataFile.print(mag.magnetic.y);
  dataFile.print(",");
  dataFile.print(mag.magnetic.z);
  dataFile.print(",");
  dataFile.print(gyro.gyro.x);
  dataFile.print(",");
  dataFile.print(gyro.gyro.y);
  dataFile.print(",");
  dataFile.print(gyro.gyro.z);
  dataFile.print(",");
}

void readSGP30ToSD() {
  if (sgp.IAQmeasure()) {
    dataFile.print(sgp.CO2);
    dataFile.print(",");
    dataFile.print(sgp.TVOC);
    dataFile.print(",");
  } else {
    Serial.println("Error reading SGP30 values");
  }
}

void readGPSToSD() {
  while (Serial1.available() > 0) {
    if (gps.encode(Serial1.read())) {
      if (gps.location.isValid()) {
        dataFile.print(gps.location.lat(), 6);
        dataFile.print(",");
        dataFile.print(gps.location.lng(), 6);
        dataFile.print(",");
        dataFile.print(gps.altitude.meters());
        dataFile.print(",");
        dataFile.print(gps.date.month());
        dataFile.print("/");
        dataFile.print(gps.date.day());
        dataFile.print("/");
        dataFile.print(gps.date.year());
        dataFile.print(",");
        dataFile.print(gps.time.hour());
        dataFile.print(":");
        dataFile.print(gps.time.minute());
        dataFile.print(":");
        dataFile.print(gps.time.second());
      }
    }
  }
}
