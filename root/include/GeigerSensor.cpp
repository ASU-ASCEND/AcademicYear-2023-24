#include "GeigerSensor.h"

const String& GeigerSensor::getSensorName() const {
    return nameCompiled;
}

const String& GeigerSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool GeigerSensor::verifyPin() {
    return true;
}

String GeigerSensor::readData(){
    Serial.begin(9600, SERIAL_8N1); // default protocal - added to be explicit 

    // reads serial output --> "CPS, #####, CPM, #####, uSv/hr, ###.##, SLOW|FAST|INST"
    String input = Serial.readStringUntil('\r'); // I think it's deliminated by carriage return
    Serial.println(input);
    // for(int i = 0; i < 7; i++){ 
    //     String input = Serial.readStringUntil(','); 
    //     Serial.println(input); 
    // }
    
}