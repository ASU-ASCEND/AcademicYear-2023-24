#include "LSM6DSOXSensor.h"

const String& LSM6DSOXSensor::getSensorName() const {
    return nameCompiled;
}

const String& LSM6DSOXSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool LSM6DSOXSensor::verifyPin() {
    // return false;
    bool connection = IMU.begin();
    IMU.end();
    return connection;
}
// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ, Temp
String readIMUData() {
    float gyroX, gyroY, gyroZ;
    IMU.readGyroscope(gyroX, gyroY, gyroZ);

    float accX, accY, accZ;
    IMU.readAcceleration(accX, accY, accZ);

    float temp;
    IMU.readTemperatureFloat(temp);

    return String(accX) + ", " + String(accY) + ", " + String(accZ) + ", " + String(gyroX) + ", " + String(gyroY) + ", " + String(gyroZ) + ", " + String(temp) + ", "; 
}

// returns in format AccX, AccY, AccZ, GyroX, GyroY, GyroZ, Temp
String LSM6DSOXSensor::readData(){
    // return "-. -. -. -. -. -. ";
    if(IMU.begin()) {
        return readIMUData();
    }
    else {
        return "-, -, -, -, -, -, -, ";
    }
}
