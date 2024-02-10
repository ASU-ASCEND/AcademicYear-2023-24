// 6 axis IMU built into the board 

#ifndef LSM6DSOXSENSOR_H 
#define LSM6DSOXSENSOR_H

#include "Sensor.h"
#include <string.h>

class LSM6DSOXSensor : public Sensor {
    private:
        static constexpr const char* nameCompiled = "LSM6DS";
        static constexpr const char* csvHeaderCompiled = "LSM6DS AccX, LSM6DS AccY, LSM6DS AccZ, LSM6DS GyroX, LSM6DS GyroY, LSM6DS GyroZ, ";
    public:
        const std::string& getSensorName() const override;
        const std::string& getSensorCSVHeader() const; 
        bool verifyPin() override;
        std::string readData() override;
};

#endif