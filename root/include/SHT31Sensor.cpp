#include "SHT31Sensor.h"

const std::string& SHT31Sensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& SHT31Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool SHT31Sensor::verifyPin() override {
    // return sht31.begin(0x44);
    return false;
}

// returns in format Hum, Temp, 
std::string SHT31Sensor::readData(){
    return "-. -. ";
    // float t = sht31.readTemperature();
    // float h = sht31.readHumidity();
    // return t + ", " + h + ", ";
}