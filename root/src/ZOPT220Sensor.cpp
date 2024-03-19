#include "ZOPT220Sensor.h"
#include "ZOPT220x_Control.h"

const arduino::String& ZOPT220Sensor::getSensorName() const {
    return nameCompiled;
}

const arduino::String& ZOPT220Sensor::getSensorCSVHeader() const {
    return String(csvHeaderCompiled);
} 

bool ZOPT220Sensor::verifyPin(){
    return zopt220xSetup();
}

arduino::String ZOPT220Sensor::readData() {
    // UV index
    setResolution(2);
    setGain(4);
    enableUVBSensing();

    // might need delay

    float uvIndex = getUVIndex(); // can be converted to UV Index

    // ALS - Abient Light 
    setResolution(2);
    setGain(1);
    enableALSSensing();

    // might need delay
    int it = 0;
    while(!dataAvailable() && it < 40){
        delay(10);
        it++;
    }

    long als = getALS();

    return String(uvIndex) + ", " + String(als) + ", "; 

}

