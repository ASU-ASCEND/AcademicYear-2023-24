#ifndef MAT31865SENSOR_H
#define MAT31865SENSOR_H
#include <string.h>
#include <Arduino.h>

#include "Sensor.h"
#include <Adafruit_MAX31865.h>
#include <Wire.h>

#define RREF 430.0
#define RNOMINAL 100.0

class MAX31865Sensor : public Sensor {
private:
    //Name for the sensor to be used in CSV header and console
    Adafruit_MAX31865 thermo = Adafruit_MAX31865(8, 11, 12, 13); 
    String nameCompiled = "MAX31865";
    String csvHeaderCompiled = "MAX31865 Resistance, MAX31865 Temp C, ";
    
public:
    const String& getSensorName() const override;
    const String& getSensorCSVHeader() const;
    bool verifyPin() override;
    String readData() override; 
};

#endif
