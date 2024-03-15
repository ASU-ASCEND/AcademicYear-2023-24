#include "SGP30Sensor.h"

const String& SGP30Sensor::getSensorName() const {
    return nameCompiled;
}

const String& SGP30Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool SGP30Sensor::verifyPin(){
    return sgp.begin();
}

String SGP30Sensor::readData(){
    String output = "";
    if(sgp.IAQmeasure()){
        output += String(sgp.TVOC) + ", ";
        output += String(sgp.eCO2) + ", ";
    }
    else {
        output += "-, -, ";
    }

    uint16_t TVOC_base, eCO2_base;
    if(sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
        output += String(TVOC_base) + ", " + String(eCO2_base) + ", ";
    }
    else {
        output += "-, -, ";
    }

    if(sgp.IAQmeasureRaw()){
        output += String(sgp.rawH2) + ", ";
        output += String(sgp.rawEthanol) + ", ";
    }
    else {
        output += "-, -, ";
    }
    
    return output;
}