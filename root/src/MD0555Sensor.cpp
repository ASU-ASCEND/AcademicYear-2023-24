#include "MD0555Sensor.h"

const String& MD0555Sensor::getSensorName() const {
    return nameCompiled;
}

const String& MD0555Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool MD0555Sensor::verifyPin() {
    // can't really be verified - analog will always read something, but we can guess that the wind won't be 0 so 
    return analogRead(WIND_PIN) > 100; // if the reading is low enough, we probably don't have a good connection
}

// returns in format WindSpeed, Temp
String MD0555Sensor::readData(){

    int windADunits = analogRead(WIND_PIN);

    float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);

    int tempRawAD = analogRead(TEMP_PIN);

    float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195; 

    return String(windMPH) + ", " + String(tempC) + ", ";

}