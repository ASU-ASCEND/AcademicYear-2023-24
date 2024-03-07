#include "Adafruit_SGP30.h"
#include <Wire.h>

const std::string& SGP30Sensor::getSensorName() const {
    return nameCompiled;
}

const String& LSM9DS1Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool SGP30Sensor::verifyPin(){

    return sgp.begin();
}

String SGP30Sensor::readData(){
    // TVOC returned in ppb, CO2 returned in ppm
    if (!sgp.IAQmeasure()){
        return "TVOC/CO2 Fail";
    }
    if (!sgp.IAQmeasureRaw()){
        return "H2/Ethanol Fail";
    }
    
    return String(sgp.TVOC) + ", " + String(sgp.eCO2) + ", " + String(sgp.rawH2) + ", " + String(spg.rawEthanol);

}

