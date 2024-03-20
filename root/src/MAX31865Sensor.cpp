#include "MAX31865Sensor.h"

const String& MAX31865Sensor::getSensorName() const {
    return nameCompiled;
}

const String& MAX31865Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool MAX31865Sensor::verifyPin() {
    digitalWrite(7, LOW);
    return thermo.begin(MAX31865_4WIRE);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
}

String MAX31865Sensor::readData() {
                        // ratio 
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    uint16_t rtd = thermo.readRTD();
    Serial.println(rtd);
    float ratio = rtd;
    ratio /= 32768;
    Serial.println(ratio,8);
    float resistance = RREF * ratio;
    
    float tempC = thermo.temperature(RNOMINAL, RREF); 

    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);

    return String(resistance) + ", " + String(tempC) + ", ";
    
} 