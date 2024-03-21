#ifndef INA260SENSOR_H 
#define INA260SENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino.h>
#include "Adafruit_INA260.h"

class INA260Sensor : public Sensor {
    private:
        Adafruit_INA260 ina260;
        String nameCompiled = "INA260";
        String csvHeaderCompiled = "INA260 Current mA, INA260 Bus Voltage mV, INA260 Power mW, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
        String readEmpty() override {
            return "-, -, -, ";
        }
};

#endif