#ifndef ZOPT220SENSOR_H
#define ZOPT220SENSOR_H

#include "Sensor.h"
// #include "ZOPT220x_Control.ino"
#include <string.h>
#include <Arduino.h>
#include <Wire.h>

class ZOPT220Sensor : public Sensor {
    private:
        String nameCompiled = "ZOPT220";
        String csvHeaderCompiled = "ZOPT220 UV Index, ZOPT220 Ambient Light, ";
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