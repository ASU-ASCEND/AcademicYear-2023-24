// 6 axis IMU built into the board 

#ifndef LSM6DSOXSENSOR_H 
#define LSM6DSOXSENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Arduino_LSM6DSOX.h>

class LSM6DSOXSensor : public Sensor {
    private:
        String nameCompiled = "LSM6DS";
        String csvHeaderCompiled = "LSM6DS AccX, LSM6DS AccY, LSM6DS AccZ, LSM6DS GyroX, LSM6DS GyroY, LSM6DS GyroZ, LSM6DS Temp, ";
    public:
        
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const; 
        bool verifyPin() override;
        String readData() override;
};

#endif