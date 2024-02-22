#include "LSM9DS1Sensor.h"

const std::string& LSM9DS1Sensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& LSM9DS1Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool LSM9DS1Sensor::verifyPin() override {
    return false;
    // return IMU.begin();
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ,
std::string LSM9DS1Sensor::readData(){
    return "-. -. -. -. -. -. -, -, -,";
    // float accX, accY, accZ;
    // IMU.readAcceleration(accX, accY, accZ);

    // float gyroX, gyroY, gyroZ;
    // IMU.readGyroscope(gyroX, gyroY, gyroZ);

    // float magX, magY, magZ;
    // IMU.readMageticField(magX, magY, magZ);

    // return accX + ", " + accY + ", " + accZ + ", " + gyroX + ", " + gyroY + ", " + gyroZ + ", " + magX + ", " + magY + ", " + magZ + ", ";
}