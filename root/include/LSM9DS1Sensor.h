#ifndef LSM9DS1SENSOR_H
#define LSM9DS1SENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino_LSM9DS1.h>

class LSM9DS1Sensor : public Sensor {
    private:
        static constexpr const char* nameCompiled = "LSM9DS1";
        static constexpr const char* csvHeaderCompiled = "LSM9DS1 AccX, LSM9DS1 AccY, LSM9DS1 AccZ, LSM9DS1 GyroX, LSM9DS1 GyroY, LSM9DS1 GyroZ, LSM9DS1 MagX, LSM9DS1 MagY, LSM9DS1 MagZ, ";
    public:
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const override; 
        bool verifyPin() override;
        String readData() override;
};

#endif