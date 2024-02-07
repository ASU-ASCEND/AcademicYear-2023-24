#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h> //Needed for Arduino functionalities

class Sensor {
public:
//Accessor Method to access name of sensor
virtual const String& getSensorName() const = 0;
//Accessor Method to access status of successful pin connection 
virtual bool verifyPin();
};
#endif
