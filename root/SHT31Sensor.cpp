#include "SHT31Sensor.h"

const std::string& SHT31Sensor::getSensorName() const override {
    return nameCompiled;
}

const std::string& SHT31Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool SHT31Sensor::verifyPin() override {
    return false;
}

// returns in format Hum, Temp, 
std::string SHT31Sensor::readData(){
    return "-. -. ";
}