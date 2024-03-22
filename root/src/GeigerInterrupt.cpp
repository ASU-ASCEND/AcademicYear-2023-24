#include "GeigerInterrupt.h"

const String& GeigerInterrupt::getSensorName() const{
    return nameCompiled;
}
const String& GeigerInterrupt::getSensorCSVHeader() const{
    return csvHeaderCompiled;
}

bool GeigerInterrupt::verifyPin(){
    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), geigerCounter, FALLING);
    measuringPeriodStart = millis();
    return true;
}
String GeigerInterrupt::readData(){
    int samplePeriod = millis() - measuringPeriodStart;

    noInterrupts();
    float CPS = count / (samplePeriod / 1000.0);
    count = 0;
    interrupts();

    measuringPeriodStart = millis();

    return String(CPS) + ", ";
}
