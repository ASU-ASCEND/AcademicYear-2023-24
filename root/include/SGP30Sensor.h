
#ifndef SGP30SENSOR_H 
#define SGP30SENSOR_H

#include "Sensor.h"
#include <string.h>
#include <stdint.h>
#include <Arduino.h>
#include "Adafruit_SGP30.h"

class SGP30Sensor : public Sensor {
    private:
        Adafruit_SGP30 sgp;
        String nameCompiled = "SGP30";
        String csvHeaderCompiled = "SGP30 TVOC ppb, SGP30 eCO2 ppm, SGP30 TVOC base, SGP30 eCO2 base, SGP30 Raw H2, SGP30 Raw Ethanol, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
        String readEmpty() override {
            return "-, -, -, -, -, -, ";
        }
};

#endif