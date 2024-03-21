#include "GeigerSlowSensor.h"

const String& GeigerSlowSensor::getSensorName() const {
    return nameCompiled;
}

const String& GeigerSlowSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
} 

bool GeigerSlowSensor::verifyPin() {
    timer = millis();
    return true;
}

String GeigerSlowSensor::readData() {
    if(millis() - timer < MILLIS_BETWEEN_READINGS){ // if it hasn't been 10 seconds
        return "-, ";
    }
    timer = millis();
    int start = millis();
    int count = 0;
    bool pulsing = false;
    while(millis() - start < 1000){ // poll for 1 second
        if(digitalRead(GEIGER_PIN) == HIGH && !pulsing){
            pulsing = true;
            count++;
        }
        else if(digitalRead(GEIGER_PIN) == LOW) {
            pulsing = false; 
        }
    }
    return String(count) + ", "; 
}