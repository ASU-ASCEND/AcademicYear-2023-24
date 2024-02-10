#include "LSM6DSSensor.h"

const std::string& LSM6DSSensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& LSM6DSSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool LSM6DSSensor::verifyPin() override {
    return false;
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ,
std::string LSM6DSSensor::readData(){
    return "-. -. -. -. -. -. ";
}