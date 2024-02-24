// Wind Sensor

#ifndef MD0555SENSOR_H 
#define MD0555SENSOR_H

#include "Sensor.h"
#include <string>
#include <Arduino.h>
// need to changed to the correct ones
#define WIND_PIN A0
#define TEMP_PIN A1

class LSM6DSOXSensor : public Sensor {
    private:
        static constexpr const char* nameCompiled = "MD0555";
        static constexpr const char* csvHeaderCompiled = "MD0555 Wind Speed mph, MD0555 Temp C, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif