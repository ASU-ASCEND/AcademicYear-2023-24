#ifndef SHT31SENSOR_H
#define SHT31SENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino.h>
#include "Adafruit_SHT31.h"
#include <Wire.h>

class SHT31Sensor : public Sensor {
    private:
        Adafruit_SHT31 sht31;
        String nameCompiled = "SHT31";
        String csvHeaderCompiled = "SHT31 Hum %, SHT31 Temp C, ";
    public:
        const arduino::String& getSensorName() const override;
        const arduino::String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        arduino::String readData() override;
        String readEmpty() override {
            return "-, -, ";
        }
};

#endif