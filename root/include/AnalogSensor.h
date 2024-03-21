// Wind Sensor and temp 

#ifndef ANALOGSENSOR_H 
#define ANALOGSENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino.h>
// need to changed to the correct ones
#define WIND_PIN A0
#define PT1000_PIN A3

class AnalogSensor : public Sensor {
    private:
        String nameCompiled = "Analog";
        String csvHeaderCompiled = "MD0555 Wind Speed RAW, PT1000 Temp RAW, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif