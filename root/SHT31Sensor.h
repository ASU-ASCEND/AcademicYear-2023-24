#ifndef SHT31SENSOR_H
#define SHT31SENSOR_H

#include "Sensor.h"
#include <string.h>
// #include "Adafruit_SHT31.h"

class SHT31Sensor : public Sensor {
    private:
        static constexpr const char* nameCompiled = "SHT31";
        static constexpr const char* csvHeaderCompiled = "SHT31 Hum %, SHT31 Temp C, ";
    public:
        const std::string& getSensorName() const override;
        const std::string& getSensorCSVHeader() const; 
        bool verifyPin() override;
        std::string readData() override;
}

#endif