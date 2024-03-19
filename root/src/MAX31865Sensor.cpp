#include "MAX31865Sensor.h"

const String& MAX31865Sensor::getSensorName() const {
    return nameCompiled;
}

const String& MAX31865Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool MAX31865Sensor::verifyPin() {
    thermo = Adafruit_MAX31865(8, 11, 12, 13);
    return thermo.begin(MAX31865_3WIRE);
}

String MAX31865Sensor::readData() {
                        // ratio 
    float resistance = (thermo.readRTD() / 32768.0) * RREF;
    
    float tempC = thermo.temperature(RNOMINAL, RREF); 

    return String(resistance) + ", " + String(tempC) + ", ";
} 