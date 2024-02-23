#include "SHT31Sensor.h"

const std::string& SHT31Sensor::getSensorName() const {
    return nameCompiled;
}

const std::string& SHT31Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool SHT31Sensor::verifyPin() {
    sht31 = Adafruit_SHT31();
    return sht31.begin(0x44);
    // return false;
}

// returns in format Hum, Temp, 
std::string SHT31Sensor::readData(){
    // return "-. -. ";
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    return t + ", " + h + ", ";
}