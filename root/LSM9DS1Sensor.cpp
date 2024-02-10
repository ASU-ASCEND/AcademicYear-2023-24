#include "LSM9DS1Sensor.h"

const std::string& LSM9DS1Sensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& LSM9DS1Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool LSM9DS1Sensor::verifyPin() override {
    return false;
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ,
std::string LSM9DS1Sensor::readData(){
    return "-. -. -. -. -. -. -, -, -,";
}