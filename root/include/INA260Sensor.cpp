#include "INA260Sensor.h"

const String& INA260Sensor::getSensorName() const {
    return nameCompiled;
}

const String& INA260Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
} 

bool INA260Sensor::verifyPin() {
    ina260 = Adafruit_INA260();
    return ina260.begin();
}

String INA260Sensor::readData() {
    float current = ina260.readCurrent();
    float busVoltage = ina260.readBusVoltage();
    float power = ina260.readPower();

    return String(current) + ", " + String(busVoltage) + ", " + String(power) + ", ";
}