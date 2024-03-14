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
    // I think it's deliminated by CRLF (carriage return, line feed)
    //Serial.readStringUntil('\r'); // flush input (we don't know where in the line we're connecting
    String input = " ";// Serial.readStringUntil('\r'); // read the line 
    Serial.println(input);  // print it 
    // for(int i = 0; i < 7; i++){ 
    //     String input = Serial.readStringUntil(','); 
    //     Serial.println(input); 
    // }
    
    String str = "";
    String values[7];
    int curr = 0;
    for(unsigned int i = 0; i < input.length(); i++){
        str += input[i];
        if(input[i] == ','){
            values[curr] = str;
            str = "";
            curr++;
        }
    }

    return values[1] + values[3] + values[5] + values[6];
    
}