#ifndef GEIGERSENSOR_H 
#define GEIGERSENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino.h>
// need to changed to the correct ones
#define RX 0
#define TX 1

class GeigerSensor : public Sensor {
    private:
        String nameCompiled = "Geiger Counter";
        String csvHeaderCompiled = "Geiger CPS, Geiger CPM, Geiger uSv/hr, Geiger Mode, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif