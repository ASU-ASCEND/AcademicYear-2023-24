// Wind Sensor and temp 

#ifndef GEIGERSLOWSENSOR_H 
#define GEIGERSLOWSENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino.h>
// need to changed to the correct ones
#define GEIGER_PIN A2
#define MILLIS_BETWEEN_READINGS 10000 // 10 seconds

class GeigerSlowSensor : public Sensor {
    private:
        int timer; 
        String nameCompiled = "GeigerSlow";
        String csvHeaderCompiled = "GeigerSlow CPS, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif