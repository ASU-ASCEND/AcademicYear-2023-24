#ifndef ZOPT220SENSOR_H
#define ZOPT220SENSOR_H

#include "Sensor.h"
// #include "ZOPT220x_Control.ino"
#include <string.h>
#include <Arduino.h>
#include <Wire.h>

class ZOPT220Sensor : public Sensor {
    private:
        static constexpr const char* nameCompiled = "ZOPT220";
        static constexpr const char* csvHeaderCompiled = "ZOPT220 , ";
    public:
        const arduino::String& getSensorName() const override;
        const arduino::String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        arduino::String readData() override;
};

#endif