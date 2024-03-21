#include "MAX31865Sensor.h"

const String& MAX31865Sensor::getSensorName() const {
    return nameCompiled;
}

const String& MAX31865Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool MAX31865Sensor::verifyPin() {
    // pinMode(7, OUTPUT);
    // pinMode(8, OUTPUT);
    // digitalWrite(7, HIGH);
    return thermo.begin(MAX31865_4WIRE);
    // digitalWrite(8, HIGH);
    // digitalWrite(7, LOW);
}

String MAX31865Sensor::readData() {
                        // ratio 
    // pinMode(7, OUTPUT);
    // pinMode(8, OUTPUT);
    // digitalWrite(7, HIGH);
    // digitalWrite(8, LOW);
    uint16_t rtd = thermo.readRTD();
    //Serial.println(rtd);
    float ratio = rtd;
    ratio /= 32768;
    //Serial.println(ratio,8);
    float resistance = RREF * ratio;
    
    float tempC = thermo.temperature(RNOMINAL, RREF); 

    // digitalWrite(8, HIGH);
    // digitalWrite(7, LOW);

    return String(resistance) + ", " + String(tempC) + ", ";
    
} 