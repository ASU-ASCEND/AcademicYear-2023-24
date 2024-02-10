#include "LSM6DSOXSensor.h"

const std::string& LSM6DSOXSensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& LSM6DSOXSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool LSM6DSOXSensor::verifyPin() override {
    return false;
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ,
std::string LSM6DSOXSensor::readData(){
    return "-. -. -. -. -. -. ";
}