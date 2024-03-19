#include "AnalogSensor.h"

const String& AnalogSensor::getSensorName() const {
    return nameCompiled;
}

const String& AnalogSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool AnalogSensor::verifyPin() {
    return true;
}

// returns in format WindSpeed, Temp
String AnalogSensor::readData(){

    int windADCunits = analogRead(WIND_PIN);
    int pt1000tempADC = analogRead(PT1000_PIN);

    return String(windADCunits) + ", " + String(pt1000tempADC) + ", ";
    // float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);

    // int tempRawAD = analogRead(TEMP_PIN);

    // float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195; 

    // return String(windMPH) + ", " + String(tempC) + ", ";

}