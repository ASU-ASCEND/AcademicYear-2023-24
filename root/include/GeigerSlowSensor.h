// Wind Sensor and temp 

#ifndef GEIGERSLOWSENSOR_H 
#define GEIGERSLOWSENSOR_H

#include "Sensor.h"
#include <string>
#include <Arduino.h>
// need to changed to the correct ones
#define GEIGER_PIN A2

class GeigerSlowSensor : public Sensor {
    private:
        String nameCompiled = "GeigerSlow";
        String csvHeaderCompiled = "GeigerSlow CPS, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif