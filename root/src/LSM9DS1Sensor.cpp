#include "LSM9DS1Sensor.h"

const String& LSM9DS1Sensor::getSensorName() const {
    return nameCompiled;
}

const String& LSM9DS1Sensor::getSensorCSVHeader() const {
    return String(csvHeaderCompiled);
}

bool LSM9DS1Sensor::verifyPin() {
    // return false;
    return IMU.begin();
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ,
String LSM9DS1Sensor::readData(){
    // return "-. -. -. -. -. -. -, -, -,";
    float accX, accY, accZ;
    IMU.readAcceleration(accX, accY, accZ);

    float gyroX, gyroY, gyroZ;
    IMU.readGyroscope(gyroX, gyroY, gyroZ);

    float magX, magY, magZ;
    IMU.readMagneticField(magX, magY, magZ);

    return String(accX) + ", " + String(accY) + ", " + String(accZ) + ", " + String(gyroX) + ", " + String(gyroY) + ", " 
        + String(gyroZ) + ", " + String(magX) + ", " + String(magY) + ", " + String(magZ) + ", ";
}