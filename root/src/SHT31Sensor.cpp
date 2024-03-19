#include "SHT31Sensor.h"

const arduino::String& SHT31Sensor::getSensorName() const {
    return nameCompiled;
}

const arduino::String& SHT31Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool SHT31Sensor::verifyPin() {
    sht31 = Adafruit_SHT31();
    return sht31.begin(0x44);
    // return false;
}

// returns in format Hum, Temp, 
arduino::String SHT31Sensor::readData() {
    // return "-. -. ";
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    return String(t) + ", " + String(h) + ", ";
}