#include "GeigerSensor.h"

const String& GeigerSensor::getSensorName() const {
    return nameCompiled;
}

const String& GeigerSensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool GeigerSensor::verifyPin() {
    Serial.begin(9600, SERIAL_8N1); // default protocal - added to be explicit 
}

String GeigerSensor::readData(){

    // reads serial output --> "CPS, #####, CPM, #####, uSv/hr, ###.##, SLOW|FAST|INST"
    // I think it's deliminated by CRLF (carriage return, line feed)
    Serial.flush(); 
    Serial.readStringUntil('\r');
    String input = Serial.readStringUntil('\r'); // read the line 


    return input;
    // String str = "";
    // String values[7] = {"", "", "", "", "", "", "",};
    // int curr = 0;
    // for(unsigned int i = 0; i < input.length(); i++){
    //     if(input[i] != '\n' && input[i] != '\r' && input[i] != ',' && input[i] != ' '){
    //         str += input[i];
    //     }
    //     if(input[i] == ','){
    //         values[curr] = str;
    //         str = "";
    //         curr++;
    //     }
    // }

    // return values[1] + ", " + values[3] + ", " + values[5] + ", " + values[6] + ", ";
    
}