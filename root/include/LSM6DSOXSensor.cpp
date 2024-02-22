#include "LSM6DSOXSensor.h"

const std::string& LSM6DSOXSensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& LSM6DSOXSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool LSM6DSOXSensor::verifyPin() override {
    return false;
    // return IMU.begin()
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ, Temp
std::string LSM6DSOXSensor::readData(){
    return "-. -. -. -. -. -. ";
    // float gyroX, gyroY, gyroZ;
    // IMU.readGyroscope(gyroX, gyroY, gyroZ);

    // float accX, accY, accZ;
    // IMU.readAcceleration(accX, accY, accZ);

    // float temp;
    // IMU.readTemperatureFloat(temp);

    // return accX + ", " + accY + ", " + accZ + ", " + gyroX + ", " + gyroY + ", " + gyroZ + ", " + temp + ", "; 

}