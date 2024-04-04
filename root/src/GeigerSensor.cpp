#include "GeigerSensor.h"

const String& GeigerSensor::getSensorName() const{
    return nameCompiled;
}
const String& GeigerSensor::getSensorCSVHeader() const{
    return csvHeaderCompiled;
}

bool GeigerSensor::verifyPin(){
    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), geigerCounter, FALLING);
    measuringPeriodStart = millis();
    return true;
}
String GeigerSensor::readData(){
    int samplePeriod = millis() - measuringPeriodStart;

    noInterrupts();
    float CPS = count / (samplePeriod / 1000.0);
    count = 0;
    interrupts();

    measuringPeriodStart = millis();

    return String(CPS) + ", ";
}
