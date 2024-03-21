#ifndef BME680SENSOR_H
#define BME680SENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Adafruit_BME680.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h> 

class BME680Sensor : public Sensor {
    private:
        Adafruit_BME680 bme;
        String nameCompiled = "BME680";
        String csvHeaderCompiled = "BME680 Temp C, BME680 Pressure hPa, BME680 Humidity %, BME680 Gas KOhms, BME680 Approx Alt m, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif